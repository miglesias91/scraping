#include <facebook/include/SolicitudPublicaciones.h>

using namespace scraping::facebook::comunicacion;

SolicitudPublicaciones::SolicitudPublicaciones(scraping::facebook::modelo::Pagina * pagina, herramientas::utiles::Fecha desde, herramientas::utiles::Fecha hasta, std::string id_app, std::string clave_secreta_app, unsigned int cantidad_de_tweets)
{
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    std::string uri = "/v2.12/" + pagina->getNombre() + "/feed?limit=" + std::to_string(cantidad_de_tweets);

    if (herramientas::utiles::Fecha(0, 0, 0) != desde)
    {
        uri += "&since=" + desde.getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    if (herramientas::utiles::Fecha(0, 0, 0) != hasta)
    {
        uri += "&until=" + hasta.getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    uri += "&" + id_app + "|" + clave_secreta_app;

    this->setURI(uri);

    this->setGET();
}

SolicitudPublicaciones::~SolicitudPublicaciones()
{
}
