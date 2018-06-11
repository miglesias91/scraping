#include <extraccion/include/ContenidoFacebook.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion::interfaceo;

ContenidoFacebook::ContenidoFacebook(herramientas::utiles::Json * json) : Contenido(json), medios::facebook::publicacion()
{
}

ContenidoFacebook::~ContenidoFacebook()
{
}