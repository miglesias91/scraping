#include <extraccion/include/ContenidoTwitter.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion::interfaceo;

ContenidoTwitter::ContenidoTwitter(herramientas::utiles::Json * json) : Contenido(json), medios::twitter::Tweet()
{
}

ContenidoTwitter::~ContenidoTwitter()
{
}