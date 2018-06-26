#include <extraccion/include/extractor.h>

// stl
#include <algorithm>

// medios
#include <twitter/include/Aplicacion.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/ConfiguracionScraping.h>

// extraccion
#include <extraccion/include/MedioTwitter.h>

namespace scraping::extraccion {

extractor::extractor() {}

extractor::~extractor() {}

bool extractor::extraer_facebook() {
    return false;
}

bool extractor::extraer_twitter() {
    // recupero las cuentas de twitter.
    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    gestor_analisis_diario.recuperarIDActualContenido();

    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioTwitter*> cuentas_twitter_existentes;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioTwitter>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_existentes);

    medios::twitter::ConsumidorAPI * consumidor_api_twitter = new medios::twitter::ConsumidorAPI("aXPpXInb16k0jKIswOYuUS3ly", "MhuDBpN9EtnafrIUHvJEbleJ3WKiFCSBIulwRVNvZTWoXGs2eV");
    consumidor_api_twitter->obtenerTokenDeAcceso();

    medios::twitter::Aplicacion app(consumidor_api_twitter);

    std::for_each(cuentas_twitter_existentes.begin(), cuentas_twitter_existentes.end(),
        [&app](scraping::extraccion::interfaceo::MedioTwitter* cuenta) {
        cuenta->descargar_tweets(app);

        delete cuenta;
    });

    return false;
}

bool extractor::extraer_portales() {
    return false;
}

}