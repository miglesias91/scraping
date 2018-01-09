// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>

// depuracion
#include <depuracion/include/Depurador.h>
#include <depuracion/include/ContenidoDepurable.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoAnalisis.h>

// twitter
#include <twitter/include/Cuenta.h>
#include <twitter/include/Tweet.h>

using namespace scraping;

TEST(Scraping, levantarConfigCorrectamente)
{
    ASSERT_EQ(true, ConfiguracionScraping::scrapingLocal());
    ASSERT_EQ(false, ConfiguracionScraping::scrapingDistribuido());

    ASSERT_EQ("001", ConfiguracionScraping::prefijoMedio());
    ASSERT_EQ("002", ConfiguracionScraping::prefijoContenido());
    ASSERT_EQ("003", ConfiguracionScraping::prefijoResultado());
}

TEST(Scraping, depurarAnalizarPreparar)
{
    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(50);
    scraping::extraccion::Medio::getGestorIDs()->setIdActual(150);

	// ----- EXTRACCION (simulada la parte de bajar el contenido de internet) ----- //

    std::vector<std::string> paths_textos_extraidos = { "le_doy_mi_palabra_20171228.txt" ,"le_doy_mi_palabra_20171227.txt",
        "le_doy_mi_palabra_20171225.txt" ,"le_doy_mi_palabra_20171222.txt", "le_doy_mi_palabra_20171031.txt" };

    twitter::modelo::Cuenta cuenta("le doy mi palabra");
    cuenta.asignarNuevoId();

    for (std::vector<std::string>::iterator it = paths_textos_extraidos.begin(); it != paths_textos_extraidos.end(); it++)
    {
        std::string path_texto_extraido = *it;
        
        std::ifstream archivo_texto(path_texto_extraido);

        std::stringstream sstream;
        sstream << archivo_texto.rdbuf();

        std::string texto_extraido(sstream.str());

        twitter::modelo::Tweet tweet;
        tweet.asignarNuevoId();
        tweet.setTextoTweet(texto_extraido);

        cuenta.agregarContenidoParaAnalizar(&tweet);

        IAdministradorScraping::getInstancia()->almacenar(&tweet);
    }

    IAdministradorScraping::getInstancia()->almacenar(&cuenta);

    // ----- DEPURACION ----- //

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    // recupero el contenido y medio que almacene de la etapa anterior.
    twitter::modelo::Cuenta cuenta_a_analizar;
    cuenta_a_analizar.setId(cuenta.getId()->copia());

    IAdministradorScraping::getInstancia()->recuperar(&cuenta_a_analizar);

    std::vector<unsigned long long int> ids_contenidos_a_analizar = cuenta_a_analizar.getIDsContenidosNoAnalizados();

    std::vector<extraccion::Contenido*> contenidos_a_recuperar;
    for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
    {
        extraccion::Contenido * tweet = new twitter::modelo::Tweet();
        tweet->setId(new herramientas::utiles::ID(*it));

        IAdministradorScraping::getInstancia()->recuperar(tweet);

        contenidos_a_recuperar.push_back(tweet);
    }

    for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
    {
        depuracion::ContenidoDepurable depurable_tweet(*it);

        depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&depurable_tweet);

        std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

        // ----- ANALISIS ----- //

        analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia(10);

        analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new analisis::tecnicas::ResultadoFuerzaEnNoticia();
        fuerza_en_noticia.aplicar(bolsa_de_palabras, *resultado_fuerza_en_noticia);

        fuerza_en_noticia.aplicar(bolsa_de_palabras, *resultado_fuerza_en_noticia);

        std::vector<std::pair<std::string, float>> top_20 = resultado_fuerza_en_noticia->getTop(20);

        // guardo el analisis
        analisis::ResultadoAnalisis resultado_analisis(resultado_fuerza_en_noticia);
        resultado_analisis.setId((*it)->getId()->copia());

        scraping::IAdministradorScraping::getInstancia()->almacenar(&resultado_analisis);
    }

    // elimino los contenidos xq ya no me sirven
    for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
    {
        delete *it;
    }

    // ----- PREPARACION ----- //

    // recupero todos los analisis guardados del medio.
    std::vector<analisis::ResultadoAnalisis*> resultados;
    for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
    {
        analisis::ResultadoAnalisis * resultado_analisis_a_recuperar = new analisis::ResultadoAnalisis();
        resultado_analisis_a_recuperar->setId(new herramientas::utiles::ID(*it));

        scraping::IAdministradorScraping::getInstancia()->recuperar(resultado_analisis_a_recuperar);

        resultados.push_back(resultado_analisis_a_recuperar);
    }

    // TO DO:
    // aca viene la parte de la preparacion, ver q onda:
    // 1) primero en teoria deberia integrar los resultados que estan en 'resultados' y dejarlos todos
    // en un solo registro. Para integrar deberia combinar los resultados de los terminos, es decir sumar los resultados de terminos que aparezcan
    // en mas de un analisis.
    // El formato del registro resultante deberia tener la forma de:
    // clave: <prefijo_resultado_medio><id_medio> valor[JSON]: { [ termino_A : { fuerza_en_noticia : 18.9876, sentimiento : 0.95 }, ... , termino_N : {fuerza...} ] }
    //
    // 2) dsp deberia agarrar todos los registros generados para cada medio (el paso anterior), y juntarlos en el registro diario.
}