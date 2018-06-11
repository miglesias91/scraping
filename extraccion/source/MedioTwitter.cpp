#include <extraccion/include/MedioTwitter.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion::interfaceo;

MedioTwitter::MedioTwitter(herramientas::utiles::Json * json) : Medio(json), medios::twitter::cuenta()
{
}

MedioTwitter::~MedioTwitter()
{
}