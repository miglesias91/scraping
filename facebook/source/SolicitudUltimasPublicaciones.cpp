#include <facebook/include/SolicitudUltimasPublicaciones.h>

using namespace scraping::facebook::comunicacion;

SolicitudUltimasPublicaciones::SolicitudUltimasPublicaciones(scraping::facebook::modelo::Pagina * pagina, std::string id_app, std::string clave_secreta_app, unsigned int cantidad_de_publicaciones_max)
{
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    std::string uri = "v2.12/" + pagina->getNombre() + "/feed?limit=" + std::to_string(cantidad_de_publicaciones_max);

    // si tiene ultima publicacion analizada, reemplazo el valor de since.
    if (herramientas::utiles::Fecha(0, 0, 0) != pagina->getFechaUltimaPublicacionAnalizada())
    {
        uri += "&since=" + pagina->getFechaUltimaPublicacionAnalizada().getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    uri += "&" + id_app + "|" + clave_secreta_app;

    this->setURI(uri);

    this->setGET();
}

SolicitudUltimasPublicaciones::~SolicitudUltimasPublicaciones()
{
}
