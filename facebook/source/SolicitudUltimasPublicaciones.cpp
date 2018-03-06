#include <facebook/include/SolicitudUltimasPublicaciones.h>

using namespace scraping::facebook::comunicacion;

SolicitudUltimasPublicaciones::SolicitudUltimasPublicaciones(scraping::facebook::modelo::Pagina * pagina, unsigned int cantidad_de_publicaciones_max)
{
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    //v2.12 / todo - noticias / ;

    std::string uri = "v2.12/" + pagina->getNombre() + "/feed" + pagina->getNombre() + "&limit=" + std::to_string(cantidad_de_publicaciones_max);
    //std::string uri = "/1.1/statuses/user_timeline.json?screen_name=" + cuenta->getNombre() + "&count=" + std::to_string(cantidad_de_tweets);

    // si tiene ultima publicacion analizada, reemplazo el valor de since.
    if (herramientas::utiles::Fecha(0, 0, 0) != pagina->getFechaUltimaPublicacionAnalizada())
    {
        uri += "&since=" + pagina->getFechaUltimaPublicacionAnalizada().getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    this->setURI(uri);

    this->setGET();
}

SolicitudUltimasPublicaciones::~SolicitudUltimasPublicaciones()
{
}
