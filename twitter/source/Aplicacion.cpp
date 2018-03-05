#include <twitter/include/Aplicacion.h>

// scraping
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/Logger.h>

// twitter
#include <twitter/include/SolicitudUltimosTweets.h>

using namespace scraping::twitter::modelo;
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

std::vector<Tweet*> Aplicacion::leerUltimosTweets(Cuenta * cuenta, unsigned int cantidad_de_tweets)
{
    scraping::Logger::info("leerUltimosTweets:{ cuenta: " + cuenta->getNombre() + " - cantidad de tweets: " + std::to_string(cantidad_de_tweets) + " }");

    comunicacion::SolicitudUltimosTweets solicitud_ultimos_tweets(cuenta, cantidad_de_tweets);

    cpprest::HTTPRespuesta * respuetas_con_tweets = this->consumidor_api->realizarSolicitud(&solicitud_ultimos_tweets);

    std::vector<utiles::Json*> tweets_json = respuetas_con_tweets->getJson()->getAtributoArrayJson();

    std::vector<modelo::Tweet*> tweets;
    for (std::vector<utiles::Json*>::iterator it = tweets_json.begin(); it != tweets_json.end(); it++)
    {
        Tweet * nuevo_tweet = new Tweet(*it);

        scraping::Logger::debug("leerUltimosTweets: tweet creado{ " + scraping::Logger::getDebugLog(nuevo_tweet) + " }");

        tweets.push_back(nuevo_tweet);
    }

    delete respuetas_con_tweets;

    scraping::Logger::info("leerUltimosTweets: tweets leidos: " + std::to_string(tweets.size()) + ".");

    return tweets;
}
