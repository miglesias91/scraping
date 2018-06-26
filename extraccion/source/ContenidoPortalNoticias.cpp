#include <extraccion/include/ContenidoPortalNoticias.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion::interfaceo;

ContenidoPortalNoticias::ContenidoPortalNoticias(herramientas::utiles::Json * json) : Contenido(json), medios::noticias::noticia()
{
}

ContenidoPortalNoticias::~ContenidoPortalNoticias()
{
}