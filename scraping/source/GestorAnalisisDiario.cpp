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

bool GestorAnalisisDiario::recuperar(scraping::IAlmacenable * contenido_a_recuperar) const {
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperar(contenido_a_recuperar);
}

bool GestorAnalisisDiario::almacenar(scraping::IAlmacenable * contenido_a_almacenar) const {
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenar(contenido_a_almacenar);
}

bool GestorAnalisisDiario::almacenarContenido(scraping::extraccion::Contenido * contenido_a_almacenar) const {
    return scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->almacenar(contenido_a_almacenar);
}

bool GestorAnalisisDiario::almacenarMedio(scraping::extraccion::Medio * medio_a_almacenar)  const {
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenar(medio_a_almacenar);
}

bool GestorAnalisisDiario::almacenarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_almacenar) const {
    return scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->almacenar(resultado_a_almacenar);
}

bool GestorAnalisisDiario::almacenarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_almacenar) const {
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenar(resultado_a_almacenar);
}

bool GestorAnalisisDiario::almacenarIDActualContenido() const {
    return scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->almacenarIDActual<scraping::extraccion::Contenido>();
}

bool GestorAnalisisDiario::recuperarContenido(scraping::extraccion::Contenido * contenido_a_almacenar) const {
    return IAdministradorScraping::getInstanciaAdminInfoTemporal()->recuperar(contenido_a_almacenar);
}

bool GestorAnalisisDiario::recuperarMedio(scraping::extraccion::Medio * medio_a_almacenar) const {
    return IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperar(medio_a_almacenar);
}

bool GestorAnalisisDiario::recuperarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_recuperar) const {
    return IAdministradorScraping::getInstanciaAdminInfoTemporal()->recuperar(resultado_a_recuperar);
}

bool GestorAnalisisDiario::recuperarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_recuperar) const {
    return IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperar(resultado_a_recuperar);
}

void GestorAnalisisDiario::recuperarIDActualContenido() const {
    uintmax_t id_actual_contenido = IAdministradorScraping::getInstanciaAdminInfoTemporal()->recuperarIDActual<scraping::extraccion::Contenido>();

    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(id_actual_contenido);
}

