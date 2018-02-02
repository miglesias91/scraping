
// gtest
#include <gtest/gtest.h>

// vld
#include <vld.h>

// scraping
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/ConfiguracionScraping.h>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

    scraping::ConfiguracionScraping::leerConfiguracion("config_scraping.json");

    scraping::IAdministradorScraping::crearAdministradorScrapingLocal();

    scraping::IAdministradorScraping::getInstancia()->abrirBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->abrirBD();

    int result = RUN_ALL_TESTS();

    scraping::IAdministradorScraping::getInstancia()->cerrarBD();

    scraping::IAdministradorScraping::getInstancia()->borrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->cerrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->borrarBD();

    scraping::IAdministradorScraping::liberar();

	std::getchar();

	return result;
}