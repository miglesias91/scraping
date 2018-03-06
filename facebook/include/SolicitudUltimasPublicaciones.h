#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/HTTPSolicitud.h>

// twitter
#include <facebook/include/Pagina.h>

namespace scraping
{
namespace facebook
{
namespace comunicacion
{

class SolicitudUltimasPublicaciones : public herramientas::cpprest::HTTPSolicitud
{
public:
    SolicitudUltimasPublicaciones(scraping::facebook::modelo::Pagina * cuenta, unsigned int cantidad_de_publicaciones_max = 100);
    virtual ~SolicitudUltimasPublicaciones();
};

};
};
};


