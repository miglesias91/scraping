#include <extraccion/include/MedioPortalNoticias.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion::interfaceo;

MedioPortalNoticias::MedioPortalNoticias(herramientas::utiles::Json * json) : Medio(json), medios::html::portal_noticias()
{
}

MedioPortalNoticias::~MedioPortalNoticias()
{
}
