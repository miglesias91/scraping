#include <twitter/include/SolicitudUltimosTweets.h>

using namespace scraping::twitter::comunicacion;

SolicitudUltimosTweets::SolicitudUltimosTweets(scraping::twitter::modelo::Cuenta * cuenta, unsigned int cantidad_de_tweets)
{
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    this->setURI("/1.1/statuses/user_timeline.json?screen_name=" + cuenta->getNombre() + "&count=" + std::to_string(cantidad_de_tweets));
    this->setGET();
}

SolicitudUltimosTweets::~SolicitudUltimosTweets()
{
}
