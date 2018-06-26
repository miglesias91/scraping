
#if defined(DEBUG) || defined(_DEBUG)

// vld
#include <vld.h>

#endif // DEBUG || _DEBUG

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

// scraping
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/ConfiguracionScraping.h>

int main(int argc, char **argv)
{

    //scraping::ConfiguracionScraping::leerConfiguracion("config_scraping.json");

    //scraping::IAdministradorScraping::crearAdministradorScrapingLocal();
    scraping::IAdministradorScraping::iniciar("config_scraping.json");

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->abrirBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->abrirBD();

    int result = Catch::Session().run(argc, argv);

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->cerrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->borrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->cerrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->borrarBD();

    scraping::IAdministradorScraping::liberar();

    herramientas::log::AdministradorLog::liberarTodo();

	std::getchar();

	return result;
}