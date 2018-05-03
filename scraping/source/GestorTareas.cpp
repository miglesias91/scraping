#include <scraping/include/GestorTareas.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/Logger.h>

// depuracion
#include <depuracion/include/Depurador.h>
#include <depuracion/include/ContenidoDepurable.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/Analizador.h>
#include <analisis/include/ContenidoAnalizable.h>

// preparacion
#include <preparacion/include/Preparador.h>
#include <preparacion/include/ResultadoAnalisisContenido.h>
#include <preparacion/include/ResultadoAnalisisMedio.h>
#include <preparacion/include/ResultadoAnalisisDiario.h>

// twitter
#include <twitter/include/Aplicacion.h>
#include <twitter/include/ConsumidorAPI.h>
#include <twitter/include/Cuenta.h>

// facebook
#include <facebook/include/Aplicacion.h>
#include <facebook/include/ConsumidorAPI.h>
#include <facebook/include/Pagina.h>

using namespace scraping::aplicacion;

GestorTareas::GestorTareas()
{
}

GestorTareas::~GestorTareas()
{
}

// twitter

void GestorTareas::scrapearTwitter()
{
    scraping::Logger::marca("INICIO SCRAPERO TWITTER.");

    // recupero las cuentas de twitter.
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperar<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_existentes);

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
            gestor_medios.actualizarMedio(cuenta);
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
    gestor_medios.recuperar<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_existentes);

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
            gestor_medios.actualizarMedio(cuenta_a_analizar);
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
    gestor_medios.recuperar<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_existentes);

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
                gestor_medios.actualizarMedio(cuenta_a_preparar);

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

// facebook

void GestorTareas::scrapearFacebook()
{
    scraping::Logger::marca("INICIO SCRAPERO FACEBOOK.");

    // recupero las cuentas de twitter.
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::facebook::modelo::Pagina*> paginas_facebook_existentes;
    gestor_medios.recuperar<scraping::facebook::modelo::Pagina>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas_facebook_existentes);

    scraping::facebook::ConsumidorAPI * consumidor_api_facebook = new scraping::facebook::ConsumidorAPI("929798640478438", "f36e906bf6b8445ac3ee53e95ac303a7");

    scraping::facebook::modelo::Aplicacion app(consumidor_api_facebook);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    gestor_analisis_diario.recuperarIDActualContenido();

    scraping::Logger::marca("EXTRAYENDO PUBLICACIONES DE PAGINAS DE FACEBOOK.");
    for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    {
        scraping::facebook::modelo::Pagina * pagina = *it;

        std::vector<scraping::facebook::modelo::Publicacion*> publicaciones = app.leerUltimasPublicaciones(pagina);

        for (std::vector<scraping::facebook::modelo::Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); it++)
        {
            scraping::facebook::modelo::Publicacion* publicacion = *it;

            publicacion->asignarNuevoId();

            pagina->agregarContenidoParaAnalizar(publicacion);

            gestor_analisis_diario.almacenarContenido(publicacion);
            gestor_analisis_diario.almacenarIDActualContenido();
        }

        if (0 < publicaciones.size())
        {// trajo por lo menos un tweet nuevo, entonces actualizo sus datos.
            pagina->setFechaUltimaPublicacionAnalizada(publicaciones[0]->getFechaCreacion());

            scraping::Logger::info("scrapearFacebook: { pagina = '" + pagina->getNombre() + "' - fecha_ultima_publicacion_analizada = '" + pagina->getFechaUltimaPublicacionAnalizada().getStringAAAAMMDDHHmmSS("-", " ", ":") + "' }");

            // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
            gestor_analisis_diario.almacenarMedio(pagina);

            // almaceno el id del ultimo tweet analizado.
            gestor_medios.actualizarMedio(pagina);
        }

        for (std::vector<scraping::facebook::modelo::Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); it++)
        {
            delete *it;
        }
        publicaciones.clear();
    }

    for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    {
        delete *it;
    }
    paginas_facebook_existentes.clear();

    scraping::Logger::marca("FIN SCRAPERO FACEBOOK.");
}

void GestorTareas::depurarYAnalizarFacebook()
{
    scraping::Logger::marca("INICIO DEPURACION Y ANALISIS TWITTER.");

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    // recupero el contenido y medio que almacene en "scrapearFacebook".
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::facebook::modelo::Pagina*> paginas_facebook_existentes;
    gestor_medios.recuperar<scraping::facebook::modelo::Pagina>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas_facebook_existentes);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;

    scraping::Logger::marca("DEPURANDO PUBLICACIONES DE PAGINAS.");
    for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    {
        scraping::facebook::modelo::Pagina * pagina_a_analizar = *it;

        // recupero todos los ids no analizados, sin importar la fecha.
        std::vector<unsigned long long int> ids_contenidos_a_analizar = pagina_a_analizar->getIDsContenidosNoAnalizados();

        std::vector<extraccion::Contenido*> contenidos_a_recuperar;
        for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
        {
            extraccion::Contenido * publicacion = new scraping::facebook::modelo::Publicacion();
            publicacion->setId(new herramientas::utiles::ID(*it));

            gestor_analisis.recuperarContenido(publicacion);

            contenidos_a_recuperar.push_back(publicacion);
        }

        scraping::Logger::marca("DEPURANDO PUBLICACIONES DE '" + pagina_a_analizar->getNombre() + "'.");
        for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
        {
            depuracion::ContenidoDepurable depurable_publicacion(*it);

            depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&depurable_publicacion);

            std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

            // ----- ANALISIS ----- //

            analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia;

            analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new analisis::tecnicas::ResultadoFuerzaEnNoticia();

            double factor_tamanio_bolsa = fuerza_en_noticia.aplicar(bolsa_de_palabras, *resultado_fuerza_en_noticia);

            scraping::Logger::info("depurarYAnalizarFacebook: { id_contenido = " + (*it)->getId()->string() + " - tamanio bolsa de palabras = '" + std::to_string(bolsa_de_palabras.size()) + "' - factor tamanio bolsa = '" + std::to_string(factor_tamanio_bolsa) + "' }");

            // std::vector<std::pair<std::string, float>> top_20 = resultado_fuerza_en_noticia->getTop(20);

            // guardo el analisis
            scraping::preparacion::ResultadoAnalisisContenido resultado_analisis(resultado_fuerza_en_noticia);
            resultado_analisis.setId((*it)->getId()->copia());

            gestor_analisis.almacenarResultadoAnalisis(&resultado_analisis);

            // seteo el contenido como analizado.
            pagina_a_analizar->setearContenidoComoAnalizado(*it);

            // almaceno las listas de ids analizados.
            gestor_medios.actualizarMedio(pagina_a_analizar);
        }

        // elimino los contenidos xq ya no me sirven
        for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
        {
            delete *it;
        }
        contenidos_a_recuperar.clear();
    }

    for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    {
        delete *it;
    }
    paginas_facebook_existentes.clear();

    scraping::Logger::marca("FIN DEPURACION Y ANALISIS FACEBOOK.");
}

void GestorTareas::prepararYAlmacenarFacebook()
{
    scraping::Logger::marca("INICIO PREPARACION Y ALMACENAMIENTO FACEBOOK.");

    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::facebook::modelo::Pagina*> paginas_facebook_existentes;
    gestor_medios.recuperar<scraping::facebook::modelo::Pagina>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas_facebook_existentes);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;

    for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    {
        scraping::facebook::modelo::Pagina * pagina_a_preparar = *it;

        std::vector<std::pair<std::string, std::vector<unsigned long long int>>> mapa_ids_contenidos_analizados = pagina_a_preparar->getParesIDsContenidosAnalizados();

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
            resultado_combinado->setId(pagina_a_preparar->getId()->copia());

            unsigned int cantidad_fuerzas_sumadas = preparador.combinar(resultados, resultado_combinado);

            scraping::preparacion::ResultadoAnalisisDiario resultado_diario_recuperado;
            resultado_diario_recuperado.setId(new herramientas::utiles::ID(std::stoul(string_fecha)));

            gestor_analisis.recuperarResultadoAnalisisDiario(&resultado_diario_recuperado);

            resultado_diario_recuperado.agregarResultadoDeMedio(resultado_combinado);

            delete resultado_combinado;

            gestor_analisis.almacenarResultadoAnalisisDiario(&resultado_diario_recuperado);

            scraping::Logger::info("prepararYAlmacenarFacebook: { fecha = '" + string_fecha + "' - id_pagina = " + pagina_a_preparar->getId()->string() + " - cantidad de resultados combinados = '" + std::to_string(resultados.size()) + "' - cantidad fuerzas sumadas = '" + std::to_string(cantidad_fuerzas_sumadas) + "' }");

            // actualizo el los ids historicos del medio y elimino los resultados
            for (std::vector<analisis::ResultadoAnalisis*>::iterator it = resultados.begin(); it != resultados.end(); it++)
            {
                extraccion::Contenido * contenido_historico = new facebook::modelo::Publicacion();
                contenido_historico->setId((*it)->getId()->copia());
                contenido_historico->setFecha(herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(string_fecha));

                pagina_a_preparar->setearContenidoComoHistorico(contenido_historico);

                // almaceno las listas de ids historicos.
                gestor_medios.actualizarMedio(pagina_a_preparar);

                delete *it;

                delete contenido_historico;
            }
            resultados.clear();
        }
    }

    for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    {
        delete *it;
    }
    paginas_facebook_existentes.clear();

    scraping::Logger::marca("FIN PREPARACION Y ALMACENAMIENTO FACEBOOK.");
}

// general

void GestorTareas::depurarYAnalizarContenidos()
{
    scraping::Logger::marca("INICIO DEPURACION Y ANALISIS DE CONTENIDOS.");

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    // recupero el contenido y medio que almacene en "scrapearFacebook".
    scraping::aplicacion::GestorMedios gestor_medios;
    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;

    std::vector<scraping::extraccion::Contenido*> contenidos_a_analizar;
    std::unordered_map<unsigned long long int, extraccion::Medio*> mapa_contenido_medio;

    // agrego los contenidos de facebook
    std::vector<scraping::facebook::modelo::Pagina*> paginas_facebook_existentes;
    gestor_medios.recuperar<scraping::facebook::modelo::Pagina>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas_facebook_existentes);

    for (auto & pagina : paginas_facebook_existentes)
    {
        std::vector<unsigned long long int> ids_contenidos_a_analizar = pagina->getIDsContenidosNoAnalizados();
        std::for_each(ids_contenidos_a_analizar.begin(), ids_contenidos_a_analizar.end(),
            [&contenidos_a_analizar, &gestor_analisis, &mapa_contenido_medio, &pagina](unsigned long long int id)
        {
            extraccion::Contenido * publicacion = new scraping::facebook::modelo::Publicacion();
            publicacion->setId(new herramientas::utiles::ID(id));

            gestor_analisis.recuperarContenido(publicacion);

            contenidos_a_analizar.push_back(publicacion);

            mapa_contenido_medio.insert(std::make_pair(id, pagina));
        });
    }

    // agrego los contenidos de twitter
    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperar<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_existentes);

    for (auto & cuenta : cuentas_twitter_existentes)
    {
        std::vector<unsigned long long int> ids_contenidos_a_analizar = cuenta->getIDsContenidosNoAnalizados();
        std::for_each(ids_contenidos_a_analizar.begin(), ids_contenidos_a_analizar.end(),
            [&contenidos_a_analizar, &gestor_analisis, &mapa_contenido_medio, &cuenta](unsigned long long int id)
        {
            extraccion::Contenido * tweet = new scraping::twitter::modelo::Tweet();
            tweet->setId(new herramientas::utiles::ID(id));

            gestor_analisis.recuperarContenido(tweet);

            contenidos_a_analizar.push_back(tweet);

            mapa_contenido_medio.insert(std::make_pair(id, cuenta));
        });
    }

    scraping::Logger::marca("ANALIZANDO CONTENIDOS.");

    // analizo los contenidos.
    analisis::Analizador analizador;
    std::for_each(contenidos_a_analizar.begin(), contenidos_a_analizar.end(),
        [&depurador, &analizador, &gestor_analisis, &gestor_medios, &mapa_contenido_medio](extraccion::Contenido * contenido)
    {
        depuracion::ContenidoDepurable depurable_publicacion(contenido);
        depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&depurable_publicacion);

        analisis::IAnalizable * contenido_analizable = new analisis::ContenidoAnalizable(contenido_depurado.getBolsaDePalabras(), contenido->getTexto().size());

        preparacion::ResultadoAnalisisContenido resultado_analisis_contenido;
        analizador.analizar(contenido_analizable, &resultado_analisis_contenido);

        resultado_analisis_contenido.setId(contenido->getId()->copia());

        gestor_analisis.almacenarResultadoAnalisis(&resultado_analisis_contenido);

        extraccion::Medio * medio_a_actualizar = mapa_contenido_medio[contenido->getId()->numero()];

        // seteo el contenido como analizado.
        medio_a_actualizar->setearContenidoComoAnalizado(contenido);

        // almaceno las listas de ids analizados.
        gestor_medios.actualizarMedio(medio_a_actualizar);
    });

    // libero memoria
    for (auto & contenido_a_borrar : contenidos_a_analizar)
    {
        delete contenido_a_borrar;
    }
    contenidos_a_analizar.clear();

    for (auto & cuenta : cuentas_twitter_existentes)
    {
        delete cuenta;
    }
    cuentas_twitter_existentes.clear();

    for (auto & pagina : paginas_facebook_existentes)
    {
        delete pagina;
    }
    cuentas_twitter_existentes.clear();
    
    scraping::Logger::marca("FIN DEPURACION Y ANALISIS DE CONTENIDOS.");

    //for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    //{
    //    scraping::facebook::modelo::Pagina * pagina_a_analizar = *it;

    //    // recupero todos los ids no analizados, sin importar la fecha.
    //    std::vector<unsigned long long int> ids_contenidos_a_analizar = pagina_a_analizar->getIDsContenidosNoAnalizados();

    //    std::vector<extraccion::Contenido*> contenidos_a_recuperar;
    //    for (std::vector<unsigned long long int>::iterator it = ids_contenidos_a_analizar.begin(); it != ids_contenidos_a_analizar.end(); it++)
    //    {
    //        extraccion::Contenido * publicacion = new scraping::facebook::modelo::Publicacion();
    //        publicacion->setId(new herramientas::utiles::ID(*it));

    //        gestor_analisis.recuperarContenido(publicacion);

    //        contenidos_a_recuperar.push_back(publicacion);
    //    }

    //    scraping::Logger::marca("DEPURANDO PUBLICACIONES DE '" + pagina_a_analizar->getNombre() + "'.");
    //    for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
    //    {
    //        depuracion::ContenidoDepurable depurable_publicacion(*it);

    //        depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&depurable_publicacion);

    //        std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

    //        // ----- ANALISIS ----- //

    //        analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    //        analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new analisis::tecnicas::ResultadoFuerzaEnNoticia();

    //        double factor_tamanio_bolsa = fuerza_en_noticia.aplicar(bolsa_de_palabras, *resultado_fuerza_en_noticia);

    //        scraping::Logger::info("depurarYAnalizarFacebook: { id_contenido = " + (*it)->getId()->string() + " - tamanio bolsa de palabras = '" + std::to_string(bolsa_de_palabras.size()) + "' - factor tamanio bolsa = '" + std::to_string(factor_tamanio_bolsa) + "' }");

    //        // std::vector<std::pair<std::string, float>> top_20 = resultado_fuerza_en_noticia->getTop(20);

    //        // guardo el analisis
    //        scraping::preparacion::ResultadoAnalisisContenido resultado_analisis(resultado_fuerza_en_noticia);
    //        resultado_analisis.setId((*it)->getId()->copia());

    //        gestor_analisis.almacenarResultadoAnalisis(&resultado_analisis);

    //        // seteo el contenido como analizado.
    //        pagina_a_analizar->setearContenidoComoAnalizado(*it);

    //        // almaceno las listas de ids analizados.
    //        gestor_medios.actualizarMedio(pagina_a_analizar);
    //    }

        // elimino los contenidos xq ya no me sirven
    //    for (std::vector<extraccion::Contenido*>::iterator it = contenidos_a_recuperar.begin(); it != contenidos_a_recuperar.end(); it++)
    //    {
    //        delete *it;
    //    }
    //    contenidos_a_recuperar.clear();
    //}

    //for (std::vector<scraping::facebook::modelo::Pagina*>::iterator it = paginas_facebook_existentes.begin(); it != paginas_facebook_existentes.end(); it++)
    //{
    //    delete *it;
    //}
    //paginas_facebook_existentes.clear();

    //scraping::Logger::marca("FIN DEPURACION Y ANALISIS FACEBOOK.");
}
