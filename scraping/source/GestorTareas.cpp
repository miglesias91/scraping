#include <scraping/include/GestorTareas.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/Logger.h>

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
    scraping::Logger::marca("INICIO SCRAPERO TWITTER.");

    // recupero las cuentas de twitter.
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperarCuentasDeTwitter(cuentas_twitter_existentes);

    scraping::twitter::ConsumidorAPI * consumidor_api_twitter = new scraping::twitter::ConsumidorAPI("aXPpXInb16k0jKIswOYuUS3ly", "MhuDBpN9EtnafrIUHvJEbleJ3WKiFCSBIulwRVNvZTWoXGs2eV");
    consumidor_api_twitter->obtenerTokenDeAcceso();

    scraping::twitter::modelo::Aplicacion app(consumidor_api_twitter);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    gestor_analisis_diario.recuperarIDActualContenido();

    scraping::Logger::marca("EXTRAYENDO TWEETS DE CUENTAS.");
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
            gestor_analisis_diario.almacenarIDActualContenido();
        }

        if(0 < tweets.size())
        {// trajo por lo menos un tweet nuevo, entonces actualizo sus datos.
            cuenta->setIdUltimoTweetAnalizado(tweets[0]->getIdTweet());

            scraping::Logger::info("scrapearTwitter: { cuenta = '" + cuenta->getNombre() + "' - id_ultimo_tweet_analizado = '" + std::to_string(cuenta->getIdUltimoTweetAnalizado()) + "' }");

            // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
            gestor_analisis_diario.almacenarMedio(cuenta);

            // almaceno el id del ultimo tweet analizado.
            gestor_medios.actualizarCuentaDeTwitter(cuenta);
        }

        for (std::vector<scraping::twitter::modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
        {
            delete *it;
        }
        tweets.clear();
    }

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_existentes.clear();

    scraping::Logger::marca("FIN SCRAPERO TWITTER.");
}

void GestorTareas::depurarYAnalizarTwitter()
{
    scraping::Logger::marca("INICIO DEPURACION Y ANALISIS TWITTER.");

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    // recupero el contenido y medio que almacene en "scrapearTwitter".
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperarCuentasDeTwitter(cuentas_twitter_existentes);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;

    scraping::Logger::marca("DEPURANDO TWEETS DE CUENTAS.");
    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        scraping::twitter::modelo::Cuenta * cuenta_a_analizar = *it;

        // recupero todos los ids no analizados, sin importar la fecha.
        std::vector<unsigned long long int> ids_contenidos_a_analizar = cuenta_a_analizar->getIDsContenidosNoAnalizados();

        std::vector<extraccion::Contenido*> contenidos_a_recuperar;
        for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
        {
            extraccion::Contenido * tweet = new twitter::modelo::Tweet();
            tweet->setId(new herramientas::utiles::ID(*it));

            gestor_analisis.recuperarContenido(tweet);

            contenidos_a_recuperar.push_back(tweet);
        }

        scraping::Logger::marca("DEPURANDO TWEETS DE '" + cuenta_a_analizar->getNombre() + "'.");
        for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
        {
            depuracion::ContenidoDepurable depurable_tweet(*it);

            depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&depurable_tweet);

            std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

            // ----- ANALISIS ----- //

            analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia;

            analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new analisis::tecnicas::ResultadoFuerzaEnNoticia();

            double factor_tamanio_bolsa = fuerza_en_noticia.aplicar(bolsa_de_palabras, *resultado_fuerza_en_noticia);

            scraping::Logger::info("depurarYAnalizarTwitter: { id_contenido = " + (*it)->getId()->string() + " - tamanio bolsa de palabras = '" + std::to_string(bolsa_de_palabras.size()) + "' - factor tamanio bolsa = '" + std::to_string(factor_tamanio_bolsa) + "' }");

            // std::vector<std::pair<std::string, float>> top_20 = resultado_fuerza_en_noticia->getTop(20);

            // guardo el analisis
            scraping::preparacion::ResultadoAnalisisContenido resultado_analisis(resultado_fuerza_en_noticia);
            resultado_analisis.setId((*it)->getId()->copia());

            gestor_analisis.almacenarResultadoAnalisis(&resultado_analisis);

            // seteo el contenido como analizado.
            cuenta_a_analizar->setearContenidoComoAnalizado(*it);

            // almaceno las listas de ids analizados.
            gestor_medios.actualizarCuentaDeTwitter(cuenta_a_analizar);
        }

        // elimino los contenidos xq ya no me sirven
        for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
        {
            delete *it;
        }
        contenidos_a_recuperar.clear();
    }

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_existentes.clear();

    scraping::Logger::marca("FIN DEPURACION Y ANALISIS TWITTER.");
}

void GestorTareas::prepararYAlmacenarTwitter()
{
    scraping::Logger::marca("INICIO PREPARACION Y ALMACENAMIENTO TWITTER.");

    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperarCuentasDeTwitter(cuentas_twitter_existentes);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        scraping::twitter::modelo::Cuenta * cuenta_a_preparar = *it;

        std::vector<std::pair<std::string, std::vector<unsigned long long int>>> mapa_ids_contenidos_analizados = cuenta_a_preparar->getParesIDsContenidosAnalizados();

        for (std::vector<std::pair<std::string, std::vector<unsigned long long int>>>::iterator it = mapa_ids_contenidos_analizados.begin(); it != mapa_ids_contenidos_analizados.end(); it++)
        {
            std::string string_fecha = it->first;
            std::vector<unsigned long long int> ids_contenidos_analizados_por_fecha = it->second;

            if (ids_contenidos_analizados_por_fecha.empty())
            {// si no hay ids para analizar, entonces sigo con la siguiente lista de ids.
                continue;
            }

            std::vector<analisis::ResultadoAnalisis*> resultados;
            for (std::vector<unsigned long long int>::iterator it = ids_contenidos_analizados_por_fecha.begin(); it != ids_contenidos_analizados_por_fecha.end(); it++)
            {
                analisis::ResultadoAnalisis * resultado_analisis_a_recuperar = new preparacion::ResultadoAnalisisContenido();
                resultado_analisis_a_recuperar->setId(new herramientas::utiles::ID(*it));

                gestor_analisis.recuperarResultadoAnalisis(resultado_analisis_a_recuperar);

                resultados.push_back(resultado_analisis_a_recuperar);
            }

            preparacion::Preparador preparador;

            preparacion::ResultadoAnalisisMedio * resultado_combinado = new preparacion::ResultadoAnalisisMedio();
            resultado_combinado->setId(cuenta_a_preparar->getId()->copia());

            unsigned int cantidad_fuerzas_sumadas = preparador.combinar(resultados, resultado_combinado);

            scraping::preparacion::ResultadoAnalisisDiario resultado_diario_recuperado;
            resultado_diario_recuperado.setId(new herramientas::utiles::ID(std::stoul(string_fecha)));

            gestor_analisis.recuperarResultadoAnalisisDiario(&resultado_diario_recuperado);

            resultado_diario_recuperado.agregarResultadoDeMedio(resultado_combinado);

            delete resultado_combinado;

            gestor_analisis.almacenarResultadoAnalisisDiario(&resultado_diario_recuperado);
            
            scraping::Logger::info("prepararYAlmacenarTwitter: { fecha = '" + string_fecha + "' - id_cuenta = " + cuenta_a_preparar->getId()->string() + " - cantidad de resultados combinados = '" + std::to_string(resultados.size()) + "' - cantidad fuerzas sumadas = '" + std::to_string(cantidad_fuerzas_sumadas) + "' }");

            // actualizo el los ids historicos del medio y elimino los resultados
            for (std::vector<analisis::ResultadoAnalisis*>::iterator it = resultados.begin(); it != resultados.end(); it++)
            {
                extraccion::Contenido * contenido_historico = new twitter::modelo::Tweet();
                contenido_historico->setId((*it)->getId()->copia());
                contenido_historico->setFecha(herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(string_fecha));

                cuenta_a_preparar->setearContenidoComoHistorico(contenido_historico);

                // almaceno las listas de ids historicos.
                gestor_medios.actualizarCuentaDeTwitter(cuenta_a_preparar);

                delete *it;

                delete contenido_historico;
            }
            resultados.clear();
        }
    }

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
    cuentas_twitter_existentes.clear();

    scraping::Logger::marca("FIN PREPARACION Y ALMACENAMIENTO TWITTER.");
}
