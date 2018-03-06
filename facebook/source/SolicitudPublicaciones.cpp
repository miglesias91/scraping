#include <facebook/include/SolicitudPublicaciones.h>

using namespace scraping::facebook::comunicacion;

SolicitudPublicaciones::SolicitudPublicaciones(scraping::facebook::modelo::Pagina * pagina, herramientas::utiles::Fecha desde, herramientas::utiles::Fecha hasta, unsigned int cantidad_de_tweets)
{
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    //v2.12 / todo - noticias / ;

    std::string uri = "v2.12/" + pagina->getNombre() + "/feed?limit=" + std::to_string(cantidad_de_tweets);
    //std::string uri = "/1.1/statuses/user_timeline.json?screen_name=" + cuenta->getNombre() + "&count=" + std::to_string(cantidad_de_tweets);

    if (herramientas::utiles::Fecha(0, 0, 0) != desde)
    {
        uri += "&since=" + desde.getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    if (herramientas::utiles::Fecha(0, 0, 0) != hasta)
    {
        uri += "&until=" + hasta.getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    this->setURI(uri);

    this->setGET();
}

SolicitudPublicaciones::~SolicitudPublicaciones()
{
}
