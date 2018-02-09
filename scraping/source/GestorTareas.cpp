#include <scraping/include/GestorTareas.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/IAdministradorScraping.h>

// depuracion
#include <depuracion/include/Depurador.h>
#include <depuracion/include/ContenidoDepurable.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>

// preparacion
#include <preparacion/include/Preparador.h>
#include <preparacion/include/ResultadoAnalisisContenido.h>
#include <preparacion/include/ResultadoAnalisisMedio.h>
#include <preparacion/include/ResultadoAnalisisDiario.h>

// twitter
#include <twitter/include/Aplicacion.h>
#include <twitter/include/ConsumidorAPI.h>
#include <twitter/include/Cuenta.h>

using namespace scraping::aplicacion;

GestorTareas::GestorTareas()
{
}

GestorTareas::~GestorTareas()
{
}

void GestorTareas::scrapearTwitter()
{
    // recupero las cuentas de twitter.
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperarCuentasDeTwitter(cuentas_twitter_existentes);

    scraping::twitter::ConsumidorAPI * consumidor_api_twitter = new scraping::twitter::ConsumidorAPI("aXPpXInb16k0jKIswOYuUS3ly", "MhuDBpN9EtnafrIUHvJEbleJ3WKiFCSBIulwRVNvZTWoXGs2eV");
    consumidor_api_twitter->obtenerTokenDeAcceso();

    scraping::twitter::modelo::Aplicacion app(consumidor_api_twitter);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        scraping::twitter::modelo::Cuenta * cuenta = *it;

        std::vector<scraping::twitter::modelo::Tweet*> tweets = app.leerUltimosTweets(cuenta);
        
        for (std::vector<scraping::twitter::modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
        {
            scraping::twitter::modelo::Tweet* tweet = *it;

            tweet->asignarNuevoId();

            cuenta->agregarContenidoParaAnalizar(tweet);

            gestor_analisis_diario.almacenarContenido(tweet);
        }

        for (std::vector<scraping::twitter::modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
        {
            delete *it;
        }
        tweets.clear();

        if(0 > tweets.size())
        {// trajo por lo menos un tweet nuevo, entonces actualizo sus datos.
            cuenta->setIdUltimoTweetAnalizado(tweets[0]->getIdTweet());
            gestor_analisis_diario.almacenarMedio(cuenta);
            gestor_medios.actualizarCuentaDeTwitter(cuenta);
        }
    }

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_existentes.clear();
}

void GestorTareas::depurarYAnalizarTwitter()
{
    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    // recupero el contenido y medio que almacene en "scrapearTwitter".
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperarCuentasDeTwitter(cuentas_twitter_existentes);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        scraping::twitter::modelo::Cuenta * cuenta_a_analizar = *it;

        std::vector<unsigned long long int> ids_contenidos_a_analizar = cuenta_a_analizar->getIDsContenidosNoAnalizados();

        std::vector<extraccion::Contenido*> contenidos_a_recuperar;
        for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
        {
            extraccion::Contenido * tweet = new twitter::modelo::Tweet();
            tweet->setId(new herramientas::utiles::ID(*it));

            gestor_analisis.recuperarContenido(tweet);

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

            std::vector<std::pair<std::string, float>> top_20 = resultado_fuerza_en_noticia->getTop(20);

            // guardo el analisis
            scraping::preparacion::ResultadoAnalisisContenido resultado_analisis(resultado_fuerza_en_noticia);
            resultado_analisis.setId((*it)->getId()->copia());

            //scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&resultado_analisis);
            gestor_analisis.almacenarResultadoAnalisis(&resultado_analisis);

            cuenta_a_analizar->setearContenidoComoAnalizado(*it);

            gestor_medios.actualizarCuentaDeTwitter(cuenta_a_analizar);
        }

        // elimino los contenidos xq ya no me sirven
        for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
        {
            delete *it;
        }
    }

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_existentes.clear();
}

void GestorTareas::prepararYAlmacenarTwitter()
{
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperarCuentasDeTwitter(cuentas_twitter_existentes);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        scraping::twitter::modelo::Cuenta * cuenta_a_preparar = *it;

        std::vector<unsigned long long int> ids_contenidos_analizados = cuenta_a_preparar->getIDsContenidosAnalizados();

        std::vector<analisis::ResultadoAnalisis*> resultados;
        for (std::vector<unsigned long long int>::iterator it = ids_contenidos_analizados.begin(); it != ids_contenidos_analizados.end(); it++)
        {
            analisis::ResultadoAnalisis * resultado_analisis_a_recuperar = new preparacion::ResultadoAnalisisContenido();
            resultado_analisis_a_recuperar->setId(new herramientas::utiles::ID(*it));

            //scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(resultado_analisis_a_recuperar);
            gestor_analisis.recuperarResultadoAnalisis(resultado_analisis_a_recuperar);

            resultados.push_back(resultado_analisis_a_recuperar);
        }

        preparacion::Preparador preparador;

        analisis::ResultadoAnalisis * resultado_combinado = new preparacion::ResultadoAnalisisContenido();
        preparador.combinar(resultados, resultado_combinado);

        preparacion::ResultadoAnalisisMedio * resultados_medio = new preparacion::ResultadoAnalisisMedio();
        resultados_medio->setId(cuenta_a_preparar->getId()->copia());

        //scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultados_medio);
        gestor_analisis.recuperarResultadoAnalisis(resultados_medio);

        resultados_medio->combinarCon(resultado_combinado);

        delete resultado_combinado;

        scraping::preparacion::ResultadoAnalisisDiario resultado_diario_recuperado;
        resultado_diario_recuperado.setId(scraping::preparacion::ResultadoAnalisisDiario::getIDDiario().copia());

        //scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultado_diario_recuperado);
        gestor_analisis.recuperarResultadoAnalisisDiario(&resultado_diario_recuperado);

        resultado_diario_recuperado.agregarResultadoDeMedio(resultados_medio);

        gestor_analisis.almacenarResultadoAnalisisDiario(&resultado_diario_recuperado);

        // elimino los resultados
        for (std::vector<analisis::ResultadoAnalisis*>::iterator it = resultados.begin(); it != resultados.end(); it++)
        {
            delete *it;
        }
    }

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_existentes.clear();
}
