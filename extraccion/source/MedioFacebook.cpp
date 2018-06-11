#include <extraccion/include/MedioFacebook.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion::interfaceo;

MedioFacebook::MedioFacebook(herramientas::utiles::Json * json) : Medio(json), medios::facebook::pagina()
{
}

MedioFacebook::~MedioFacebook()
{
}