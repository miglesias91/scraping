#include <scraping/include/GestorTareas.h>

// scraping
#include <scraping/include/GestorMedios.h>

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

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        scraping::twitter::modelo::Cuenta * cuenta = *it;

        std::vector<scraping::twitter::modelo::Tweet> tweets = app.leerUltimosTweets(cuenta);

        for (std::vector<scraping::twitter::modelo::Tweet>::iterator it = tweets.begin(); it != tweets.end(); it++)
        {
            it->asignarNuevoId();
        }
    }

}
