#include <facebook/include/Aplicacion.h>

// scraping
#include <scraping/include/Logger.h>

// twitter
#include <facebook/include/SolicitudUltimasPublicaciones.h>
#include <facebook/include/SolicitudPublicaciones.h>

using namespace scraping::facebook::modelo;

Aplicacion::Aplicacion(scraping::facebook::ConsumidorAPI * consumidor_api) : consumidor_api(consumidor_api)
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

std::vector<Publicacion*> Aplicacion::leerUltimasPublicaciones(Pagina * cuenta, unsigned int cantidad_de_publicaciones_maximo)
{
    scraping::Logger::info("leerUltimasPublicaciones:{ cuenta: " + cuenta->getNombre() + " cantidad de publicaciones: " + std::to_string(cantidad_de_publicaciones_maximo) + " }");

    scraping::facebook::comunicacion::SolicitudUltimasPublicaciones solicitud_ultimas_publicaciones(cuenta, cantidad_de_publicaciones_maximo);

    herramientas::cpprest::HTTPRespuesta * respuetas_con_publicaciones = this->consumidor_api->realizarSolicitud(&solicitud_ultimas_publicaciones);

    std::vector<herramientas::utiles::Json*> publicaciones_json = respuetas_con_publicaciones->getJson()->getAtributoArrayJson();

    std::vector<Publicacion*> publicaciones;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++)
    {
        Publicacion * nueva_publicacion = new Publicacion(*it);

        //scraping::Logger::debug("leerUltimasPublicaciones: publicacion creada{ " + scraping::Logger::getDebugLog(nueva_publicacion) + " }");

        publicaciones.push_back(nueva_publicacion);
    }

    delete respuetas_con_publicaciones;

    scraping::Logger::info("leerUltimasPublicaciones: publicaciones leidas: " + std::to_string(publicaciones.size()) + ".");

    return publicaciones;
}

std::vector<Publicacion*> Aplicacion::leerPublicaciones(Pagina * cuenta, herramientas::utiles::Fecha desde, herramientas::utiles::Fecha hasta, unsigned int cantidad_de_publicaciones_maximo)
{
    scraping::Logger::info("leerPublicaciones:{ cuenta: " + cuenta->getNombre() + " - desde: " + desde.getStringAAAAMMDDHHmmSS() + " - hasta : " + hasta.getStringAAAAMMDDHHmmSS()  + " cantidad de publicaciones: " + std::to_string(cantidad_de_publicaciones_maximo) + " }");

    scraping::facebook::comunicacion::SolicitudPublicaciones solicitud_ultimas_publicaciones(cuenta, desde, hasta, cantidad_de_publicaciones_maximo);

    herramientas::cpprest::HTTPRespuesta * respuetas_con_publicaciones = this->consumidor_api->realizarSolicitud(&solicitud_ultimas_publicaciones);

    std::vector<herramientas::utiles::Json*> publicaciones_json = respuetas_con_publicaciones->getJson()->getAtributoArrayJson();

    std::vector<Publicacion*> publicaciones;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++)
    {
        Publicacion * nueva_publicacion = new Publicacion(*it);

        //scraping::Logger::debug("leerUltimasPublicaciones: publicacion creada{ " + scraping::Logger::getDebugLog(nueva_publicacion) + " }");

        publicaciones.push_back(nueva_publicacion);
    }

    delete respuetas_con_publicaciones;

    scraping::Logger::info("leerPublicaciones: publicaciones leidas: " + std::to_string(publicaciones.size()) + ".");

    return publicaciones;
}
