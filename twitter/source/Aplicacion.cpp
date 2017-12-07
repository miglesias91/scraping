#include <twitter/include/Aplicacion.h>

// twitter
#include <twitter/include/SolicitudUltimosTweets.h>

using namespace scraping::twitter;
using namespace herramientas;

Aplicacion::Aplicacion(ConsumidorAPI * consumidor_api) : consumidor_api(consumidor_api)
{
}

Aplicacion::~Aplicacion()
{
    if (NULL != this->consumidor_api)
    {
        delete this->consumidor_api;
        this->consumidor_api = NULL;
    }
}

std::vector<scraping::twitter::modelo::Tweet> scraping::twitter::Aplicacion::leerUltimosTweets(scraping::twitter::modelo::Usuario * usuario, unsigned int cantidad_de_tweets)
{
    comunicacion::SolicitudUltimosTweets solicitud_ultimos_tweets(usuario, cantidad_de_tweets);

    cpprest::HTTPRespuesta * respuetas_con_tweets = this->consumidor_api->realizarSolicitud(&solicitud_ultimos_tweets);

    return std::vector<scraping::twitter::modelo::Tweet>();
}
