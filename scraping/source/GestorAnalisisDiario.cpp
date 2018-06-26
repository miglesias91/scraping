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

bool scraping::aplicacion::GestorAnalisisDiario::almacenarContenido(scraping::extraccion::Contenido * contenido_a_almacenar) const {
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(contenido_a_almacenar);
}

bool GestorAnalisisDiario::almacenarMedio(scraping::extraccion::Medio * medio_a_almacenar)
{
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(medio_a_almacenar);
}

bool GestorAnalisisDiario::almacenarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_almacenar)
{
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(resultado_a_almacenar);
}

bool GestorAnalisisDiario::almacenarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_almacenar)
{
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(resultado_a_almacenar);
}

bool GestorAnalisisDiario::almacenarIDActualContenido() const {
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenarIDActual<scraping::extraccion::Contenido>();
}

bool GestorAnalisisDiario::recuperarContenido(scraping::extraccion::Contenido * contenido_a_almacenar)
{
    return IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(contenido_a_almacenar);
}

bool GestorAnalisisDiario::recuperarMedio(scraping::extraccion::Medio * medio_a_almacenar)
{
    return IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(medio_a_almacenar);
}

bool GestorAnalisisDiario::recuperarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_recuperar)
{
    return IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(resultado_a_recuperar);
}

bool GestorAnalisisDiario::recuperarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_recuperar)
{
    return IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(resultado_a_recuperar);
}

void GestorAnalisisDiario::recuperarIDActualContenido() const {
    unsigned long long int id_actual_contenido = IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperarIDActual<scraping::extraccion::Contenido>();

    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(id_actual_contenido);
}

