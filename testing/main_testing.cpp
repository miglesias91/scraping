
#define GTEST_LANG_CXX11 1

// gtest
#include <gtest/gtest.h>

#ifdef DEBUG || _DEBUG

// vld
#include <vld.h>

#endif // DEBUG || _DEBUG

// scraping
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/ConfiguracionScraping.h>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

    //scraping::ConfiguracionScraping::leerConfiguracion("config_scraping.json");

    //scraping::IAdministradorScraping::crearAdministradorScrapingLocal();
    scraping::IAdministradorScraping::iniciar("config_scraping.json");

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->abrirBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->abrirBD();

    int result = RUN_ALL_TESTS();

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->cerrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->borrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->cerrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->borrarBD();

    scraping::IAdministradorScraping::liberar();

    herramientas::log::AdministradorLog::liberarTodo();

	std::getchar();

	return result;
}