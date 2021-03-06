#include <extraccion/include/extractor.h>

// stl
#include <algorithm>

// medios
#include <twitter/include/Aplicacion.h>
#include <facebook/include/Aplicacion.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/ConfiguracionScraping.h>

// extraccion
#include <extraccion/include/MedioTwitter.h>
#include <extraccion/include/MedioFacebook.h>
#include <extraccion/include/MedioPortalNoticias.h>

namespace scraping::extraccion {

extractor::extractor() {}

extractor::~extractor() {}

bool extractor::extraer_facebook() {
    scraping::Logger::info("facebook", "extraccion: iniciada.");

    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioFacebook*> paginas_facebook_existentes;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioFacebook>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas_facebook_existentes);

    scraping::Logger::info("facebook", "extraccion: " + std::to_string(paginas_facebook_existentes.size()) + " paginas existentes.");

    medios::facebook::consumidor_api * consumidor_api_twitter = new medios::facebook::consumidor_api("929798640478438", "f36e906bf6b8445ac3ee53e95ac303a7");

    medios::facebook::aplicacion app(consumidor_api_twitter);

    std::for_each(paginas_facebook_existentes.begin(), paginas_facebook_existentes.end(),
        [&app](scraping::extraccion::interfaceo::MedioFacebook* pagina) {
        pagina->descargar_publicaciones(app);

        delete pagina;
    });

    scraping::Logger::info("facebook", "extraccion: finalizada.");

    return true;
}

bool extractor::extraer_twitter() {
    scraping::Logger::info("twitter", "extraccion: iniciada.");

    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioTwitter*> cuentas_twitter_existentes;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioTwitter>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_existentes);

    scraping::Logger::info("twitter", "extraccion: " + std::to_string(cuentas_twitter_existentes.size()) + " cuentas existentes.");

    medios::twitter::ConsumidorAPI * consumidor_api_twitter = new medios::twitter::ConsumidorAPI("aXPpXInb16k0jKIswOYuUS3ly", "MhuDBpN9EtnafrIUHvJEbleJ3WKiFCSBIulwRVNvZTWoXGs2eV");
    consumidor_api_twitter->obtenerTokenDeAcceso();

    medios::twitter::Aplicacion app(consumidor_api_twitter);

    std::for_each(cuentas_twitter_existentes.begin(), cuentas_twitter_existentes.end(),
        [&app](scraping::extraccion::interfaceo::MedioTwitter* cuenta) {
        cuenta->descargar_tweets(app);

        delete cuenta;
    });

    scraping::Logger::info("twitter", "extraccion: finalizada.");

    return true;
}

bool extractor::extraer_portales() {
    scraping::Logger::info("portales", "extraccion: iniciada.");

    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioPortalNoticias*> portales_existentes;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioPortalNoticias>(scraping::ConfiguracionScraping::prefijoPortalNoticias(), portales_existentes);

    scraping::Logger::info("portales", "extraccion: " + std::to_string(portales_existentes.size()) + " portales existentes.");

    medios::noticias::lector lector;

    std::for_each(portales_existentes.begin(), portales_existentes.end(),
        [&lector](scraping::extraccion::interfaceo::MedioPortalNoticias * portal) {
        portal->descargar_noticias(lector);

        delete portal;
    });
    scraping::Logger::info("portales", "extraccion: finalizada.");

    return true;
}

}