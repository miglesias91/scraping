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

bool GestorMedios::recuperarCuentasDeTwitter(std::vector<scraping::twitter::modelo::Cuenta*> & cuentas_de_twitter)
{
    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->recuperarGrupo<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), &cuentas_de_twitter);
}

bool GestorMedios::agregarCuentaDeTwitter(scraping::extraccion::Medio * medio_nuevo)
{
    medio_nuevo->setGrupo(scraping::ConfiguracionScraping::prefijoTwitter());

    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->almacenar(medio_nuevo);
}
