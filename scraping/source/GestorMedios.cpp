#include <scraping/include/GestorMedios.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>

using namespace scraping::aplicacion;

GestorMedios::GestorMedios()
{
}

GestorMedios::~GestorMedios()
{
}

bool GestorMedios::recuperarTodos(std::vector<scraping::extraccion::Medio*>& medios)
{
    return false;
}

bool GestorMedios::actualizarCuentaDeTwitter(scraping::twitter::modelo::Cuenta * cuenta_a_actualizar)
{
    cuenta_a_actualizar->setGrupo(scraping::ConfiguracionScraping::prefijoTwitter());

    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->modificar(cuenta_a_actualizar);

    return false;
}

bool GestorMedios::recuperarCuentasDeTwitter(std::vector<scraping::twitter::modelo::Cuenta*> & cuentas_de_twitter)
{
    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->recuperarGrupo<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), &cuentas_de_twitter);
}

bool GestorMedios::agregarCuentaDeTwitter(scraping::twitter::modelo::Cuenta * medio_nuevo)
{
    medio_nuevo->setGrupo(scraping::ConfiguracionScraping::prefijoTwitter());

    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->almacenar(medio_nuevo);
}

bool GestorMedios::almacenarIDActualMedio()
{
    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->almacenarIDActual<scraping::extraccion::Medio>();
}

void GestorMedios::recuperarIDActualMedio()
{
    unsigned long long int id_actual_medio = IAdministradorScraping::getInstanciaAdminInfo()->recuperarIDActual<scraping::extraccion::Medio>();

    scraping::extraccion::Medio::getGestorIDs()->setIdActual(id_actual_medio);
}