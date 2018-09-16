
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
    //scraping::IAdministradorScraping::iniciar("config_scraping.json");

    //scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->abrirBD();

    //scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->abrirBD();

    int result = Catch::Session().run(argc, argv);

    //scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->cerrarBD();

    //scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->borrarBD();

    //scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->cerrarBD();

    //scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->borrarBD();

    //scraping::IAdministradorScraping::liberar();

	std::getchar();

	return result;
}