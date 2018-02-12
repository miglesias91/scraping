#include <twitter/include/SolicitudUltimosTweets.h>

using namespace scraping::twitter::comunicacion;

SolicitudUltimosTweets::SolicitudUltimosTweets(scraping::twitter::modelo::Cuenta * cuenta, unsigned int cantidad_de_tweets)
{
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    std::string uri = "/1.1/statuses/user_timeline.json?screen_name=" + cuenta->getNombre() + "&count=" + std::to_string(cantidad_de_tweets);

    // si tiene ultimo tweet analizado, entonces lo agrego como parametro.
    if (0 != cuenta->getIdUltimoTweetAnalizado())
    {
        uri += "&since_id=" + std::to_string(cuenta->getIdUltimoTweetAnalizado());
    }

    uri += "&trim_user=true&tweet_mode=extended";

    this->setURI(uri);

    this->setGET();
}

SolicitudUltimosTweets::~SolicitudUltimosTweets()
{
}
