// catch2
#include <catch.hpp>

// stl
#include <fstream>

// medios
#include <noticias/include/clarin.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>

// depuracion
#include <depuracion/include/Depurador.h>
#include <depuracion/include/ContenidoDepurable.h>

// analisis
#include <analisis/include/Analizador.h>
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>

// preparacion
#include <preparacion/include/Preparador.h>
#include <preparacion/include/ResultadoAnalisisContenido.h>
#include <preparacion/include/ResultadoAnalisisMedio.h>

// extraccion
#include <extraccion/include/MedioTwitter.h>
#include <extraccion/include/MedioFacebook.h>
#include <extraccion/include/MedioPortalNoticias.h>
#include <extraccion/include/extractor.h>

using namespace scraping;

TEST_CASE("levantar_config_correctamente", "scraping")
{
    REQUIRE(true == ConfiguracionScraping::scrapingLocal());
    REQUIRE(false == ConfiguracionScraping::scrapingDistribuido());

    REQUIRE("001" == ConfiguracionScraping::prefijoMedio());
    REQUIRE("002" == ConfiguracionScraping::prefijoContenido());
    REQUIRE("003" == ConfiguracionScraping::prefijoContenidoDepurado());
    REQUIRE("004" == ConfiguracionScraping::prefijoResultadoMedio());
    REQUIRE("005" == ConfiguracionScraping::prefijoResultadoContenido());
    REQUIRE("006" == ConfiguracionScraping::prefijoResultadoDiario());
}

TEST_CASE("depurar_analizar_y_preparar", "scraping[.]")
{
    //extraccion::Contenido::getGestorIDs()->setIdActual(50);
    //extraccion::Medio::getGestorIDs()->setIdActual(150);

    //// ----- EXTRACCION (simulada la parte de bajar el contenido de internet) ----- //

    //std::vector<std::string> paths_textos_extraidos = { "le_doy_mi_palabra_20171228.txt", "le_doy_mi_palabra_20171227.txt",
    //    "le_doy_mi_palabra_20171225.txt", "le_doy_mi_palabra_20171222.txt", "le_doy_mi_palabra_20171031.txt" };

    ////twitter::modelo::Cuenta cuenta("le doy mi palabra");
    ////cuenta.asignarNuevoId();
    //extraccion::interfaceo::MedioTwitter cuenta;
    //cuenta.asignarNuevoId();

    //for (std::vector<std::string>::iterator it = paths_textos_extraidos.begin(); it != paths_textos_extraidos.end(); it++)
    //{
    //    std::string path_texto_extraido = *it;

    //    std::ifstream archivo_texto(path_texto_extraido);

    //    std::stringstream sstream;
    //    sstream << archivo_texto.rdbuf();

    //    std::string texto_extraido(sstream.str());

    //    scraping::extraccion::Contenido tweet;
    //    tweet.asignarNuevoId();
    //    tweet.setTexto(texto_extraido);

    //    cuenta.agregarContenidoParaAnalizar(&tweet);

    //    IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&tweet);
    //}

    //IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&cuenta);

    //// ----- DEPURACION ----- //

    //depuracion::Depurador depurador;
    //depurador.cargarMapeoUTF8("mapeo_utf8.json");

    //// recupero el contenido y medio que almacene de la etapa anterior.
    ////twitter::modelo::Cuenta cuenta_a_analizar;
    ////cuenta_a_analizar.setId(cuenta.getId()->copia());
    //extraccion::interfaceo::MedioTwitter cuenta_a_analizar;
    //cuenta_a_analizar.setId(cuenta.getId()->copia());

    //IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&cuenta_a_analizar);

    //std::vector<unsigned long long int> ids_contenidos_a_analizar = cuenta_a_analizar.getIDsContenidosNoAnalizados();

    //std::vector<extraccion::Contenido*> contenidos_a_recuperar;
    //for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
    //{
    //    //extraccion::Contenido * tweet = new twitter::modelo::Tweet();
    //    extraccion::Contenido * tweet = new extraccion::Contenido();
    //    tweet->setId(new herramientas::utiles::ID(*it));

    //    IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(tweet);

    //    contenidos_a_recuperar.push_back(tweet);
    //}

    //for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
    //{
    //    depuracion::ContenidoDepurable depurable_tweet(*it);

    //    depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&depurable_tweet);

    //    std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

    //    // ----- ANALISIS ----- //

    //    analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia(10);

    //    analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new analisis::tecnicas::ResultadoFuerzaEnNoticia();

    //    fuerza_en_noticia.aplicar(bolsa_de_palabras, resultado_fuerza_en_noticia);

    //    std::vector<std::pair<std::string, float>> top_20 = resultado_fuerza_en_noticia->getTop(20);

    //    // guardo el analisis
    //    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis(resultado_fuerza_en_noticia);
    //    resultado_analisis.setId((*it)->getId()->copia());

    //    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&resultado_analisis);

    //    cuenta_a_analizar.setearContenidoComoAnalizado(*it);
    //}

    //// elimino los contenidos xq ya no me sirven
    //for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
    //{
    //    delete *it;
    //}

    //// ----- PREPARACION ----- //

    //// recupero todos los analisis guardados del medio.
    //std::vector<analisis::ResultadoAnalisis*> resultados;
    //for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
    //{
    //    analisis::ResultadoAnalisis * resultado_analisis_a_recuperar = new preparacion::ResultadoAnalisisContenido();
    //    resultado_analisis_a_recuperar->setId(new herramientas::utiles::ID(*it));

    //    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(resultado_analisis_a_recuperar);

    //    resultados.push_back(resultado_analisis_a_recuperar);
    //}

    //preparacion::Preparador preparador;

    //analisis::ResultadoAnalisis * resultado_combinado = new preparacion::ResultadoAnalisisContenido();
    //preparador.combinar(resultados, resultado_combinado);

    //preparacion::ResultadoAnalisisMedio resultados_medio;
    //resultados_medio.setId(cuenta.getId()->copia());

    //scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultados_medio);

    //resultados_medio.combinarCon(resultado_combinado);

    //delete resultado_combinado;

    //// elimino los resultados
    //for (std::vector<analisis::ResultadoAnalisis*>::iterator it = resultados.begin(); it != resultados.end(); it++)
    //{
    //    delete *it;
    //}

     //ResultadoAnalisisMedio resultado_por_medio;
     //resultado_por_medio.setId(id_medio);
     //
     //scraping::IAdministradorScraping::getInstancia()->recuperar(resultado_por_medio);
    
     //resultado_por_medio.combinarResultados(resultados);

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


TEST_CASE("gestor_medios_almacenar_y_eliminar_correctamente", "scraping")
{
    // creo cuentas de prueba.
    extraccion::interfaceo::MedioTwitter * cuenta_uno = new extraccion::interfaceo::MedioTwitter("cuenta_uno");
    cuenta_uno->asignarNuevoId();

    extraccion::interfaceo::MedioTwitter * cuenta_dos = new extraccion::interfaceo::MedioTwitter("cuenta_dos");
    cuenta_dos->asignarNuevoId();

    extraccion::interfaceo::MedioTwitter * cuenta_tres = new extraccion::interfaceo::MedioTwitter("cuenta_tres");
    cuenta_tres->asignarNuevoId();

    extraccion::interfaceo::MedioTwitter * cuenta_cuatro = new extraccion::interfaceo::MedioTwitter("cuenta_cuatro");
    cuenta_cuatro->asignarNuevoId();

    extraccion::interfaceo::MedioTwitter * cuenta_cinco = new extraccion::interfaceo::MedioTwitter("cuenta_cinco");
    cuenta_cinco->asignarNuevoId();

    // almaceno las cuentas.

    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<extraccion::interfaceo::MedioTwitter*> cuentas_twitter_existentes = gestor_medios.gestionar<extraccion::interfaceo::MedioTwitter>(ConfiguracionScraping::prefijoTwitter());

    gestor_medios.almacenar(cuenta_uno);
    gestor_medios.almacenar(cuenta_dos);
    gestor_medios.almacenar(cuenta_tres);
    gestor_medios.almacenar(cuenta_cuatro);
    gestor_medios.almacenar(cuenta_cinco);

    gestor_medios.guardarCambios();

    // recupero las cuentas recien almacenadas.

    std::vector<extraccion::interfaceo::MedioTwitter*> cuentas_twitter_recuperadas;
    gestor_medios.recuperar<extraccion::interfaceo::MedioTwitter>(ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_recuperadas);

    REQUIRE("cuenta_uno" == cuentas_twitter_recuperadas[0]->cuenta()->getNombre());
    REQUIRE("cuenta_dos" == cuentas_twitter_recuperadas[1]->cuenta()->getNombre());
    REQUIRE("cuenta_tres" == cuentas_twitter_recuperadas[2]->cuenta()->getNombre());

    for (std::vector<extraccion::interfaceo::MedioTwitter*>::iterator it = cuentas_twitter_recuperadas.begin(); it != cuentas_twitter_recuperadas.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_recuperadas.clear();

    // elimino 2 de las 3 cuentas recien almacenadas.

    gestor_medios.eliminar(cuenta_uno);
    gestor_medios.eliminar(cuenta_tres);

    gestor_medios.guardarCambios();

    // recupero la cuenta que me quedo.

    gestor_medios.recuperar<extraccion::interfaceo::MedioTwitter>(ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_recuperadas);

    REQUIRE("cuenta_dos" == cuentas_twitter_recuperadas[0]->cuenta()->getNombre());

    // elimino la que quedo asi no queda ninguna cuenta almacenada.

    gestor_medios.eliminar(cuenta_dos);
    gestor_medios.eliminar(cuenta_cuatro);
    gestor_medios.eliminar(cuenta_cinco);

    gestor_medios.guardarCambios();

    for (std::vector<extraccion::interfaceo::MedioTwitter*>::iterator it = cuentas_twitter_recuperadas.begin(); it != cuentas_twitter_recuperadas.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_recuperadas.clear();

    delete cuenta_uno;
    delete cuenta_dos;
    delete cuenta_tres;
    delete cuenta_cuatro;
    delete cuenta_cinco;
}

TEST_CASE("gestionar_cuentas_de_twitter", "scraping")
{
    scraping::aplicacion::GestorMedios gestor_medios;

    extraccion::interfaceo::MedioTwitter cuenta_uno("cuenta_uno");
    cuenta_uno.asignarNuevoId();

    extraccion::interfaceo::MedioTwitter cuenta_dos("cuenta_dos");
    cuenta_dos.asignarNuevoId();

    extraccion::interfaceo::MedioTwitter cuenta_tres("cuenta_tres");
    cuenta_tres.asignarNuevoId();

    gestor_medios.almacenar(&cuenta_uno);
    gestor_medios.almacenar(&cuenta_dos);
    gestor_medios.almacenar(&cuenta_tres);
    gestor_medios.guardarCambios();

    std::vector<extraccion::interfaceo::MedioTwitter*> cuentas_twitter_existentes;
    gestor_medios.recuperar<extraccion::interfaceo::MedioTwitter>(cuenta_uno.getGrupoMedio(), cuentas_twitter_existentes);

    REQUIRE("cuenta_uno" == cuentas_twitter_existentes[0]->cuenta()->getNombre());
    REQUIRE("cuenta_dos" == cuentas_twitter_existentes[1]->cuenta()->getNombre());
    REQUIRE("cuenta_tres" == cuentas_twitter_existentes[2]->cuenta()->getNombre());

    gestor_medios.eliminar(&cuenta_uno);
    gestor_medios.eliminar(&cuenta_dos);
    gestor_medios.eliminar(&cuenta_tres);
    gestor_medios.guardarCambios();

    for (std::vector<extraccion::interfaceo::MedioTwitter*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_existentes.clear();
}

TEST_CASE("scrapear_twitter", "scraping[.]") {

    extraccion::interfaceo::MedioTwitter clarin("clarincom");
    clarin.asignarNuevoId();

    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.almacenar(&clarin);
    gestor_medios.guardarCambios();

    extraccion::extractor extractor;
    extractor.extraer_twitter();

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");
    depurador.depurar_twitter();

    analisis::Analizador analizador;
    analizador.analizar_twitter();

    preparacion::Preparador preparador;
    preparador.preparar_twitter();

    gestor_medios.eliminar(&clarin);
    gestor_medios.guardarCambios();
}

TEST_CASE("scrapear_facebook", "scraping[.]") {

    extraccion::interfaceo::MedioFacebook clarin("clarincom");
    clarin.asignarNuevoId();

    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.almacenar(&clarin);
    gestor_medios.guardarCambios();

    extraccion::extractor extractor;
    extractor.extraer_facebook();

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");
    depurador.depurar_facebook();

    analisis::Analizador analizador;
    analizador.analizar_facebook();

    preparacion::Preparador preparador;
    preparador.preparar_facebook();

    gestor_medios.eliminar(&clarin);
    gestor_medios.guardarCambios();
}

TEST_CASE("scrapear_portal", "scraping") {

    extraccion::interfaceo::MedioPortalNoticias clarin(std::make_shared<medios::noticias::clarin>());
    clarin.asignarNuevoId();

    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.almacenar(&clarin);
    gestor_medios.guardarCambios();

    extraccion::extractor extractor;
    extractor.extraer_portales();

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");
    depurador.depurar_portales();

    analisis::Analizador analizador;
    analizador.analizar_portales();

    preparacion::Preparador preparador;
    preparador.preparar_portales();

    gestor_medios.eliminar(&clarin);
    gestor_medios.guardarCambios();
}