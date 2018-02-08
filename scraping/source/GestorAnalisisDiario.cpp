#include <scraping/include/GestorAnalisisDiario.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>

using namespace scraping::aplicacion;

GestorAnalisisDiario::GestorAnalisisDiario()
{
}

GestorAnalisisDiario::~GestorAnalisisDiario()
{
}

// GETTERS

// SETTERS

// METODOS

bool GestorAnalisisDiario::almacenarContenidoParaAnalizar(scraping::extraccion::Contenido * contenido_a_almacenar)
{
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(contenido_a_almacenar);
}

bool GestorAnalisisDiario::almacenarMedioConContenidoParaAnalizar(scraping::extraccion::Medio * medio_a_almacenar)
{
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(medio_a_almacenar);
}
