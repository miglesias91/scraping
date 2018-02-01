#include <scraping/include/IAdministradorScraping.h>

using namespace scraping;

// stl
#include <iostream>

// aplicacion
#include <scraping/include/AdministradorScrapingLocal.h>
#include <scraping/include/ConfiguracionScraping.h>

typedef scraping::IAdministradorScraping* (*admin)();

IAdministradorScraping* IAdministradorScraping::administrador = NULL;
IAdministradorScraping* IAdministradorScraping::administrador_info = NULL;
IAdministradorScraping* IAdministradorScraping::administrador_resultados_analisis_diario = NULL;

IAdministradorScraping::IAdministradorScraping() : admin_almacenamiento(NULL)
{
}

IAdministradorScraping::~IAdministradorScraping()
{
}

void IAdministradorScraping::iniciar(std::string path_configuracion)
{
	if (administradorIniciado())
	{
		// TODO agregar log.
		std::cout << "Scraping ya fue iniciado." << std::endl;
		return;
		// throw std::exception("Administrador ya fue iniciado.");
	}

	ConfiguracionScraping::leerConfiguracion(path_configuracion);

	if (ConfiguracionScraping::scrapingLocal())
	{
		crearAdministradorScrapingLocal();
	}
	else
	{
		crearAdministradorScrapingDistribuido();
	}
}

void IAdministradorScraping::liberar()
{
	if (true == administradorIniciado())
	{
		delete administrador;
	}

    if (true == administradorInfoIniciado())
    {
        delete administrador_info;
    }

    if (true == administradorResultadosAnalisisDiarioIniciado())
    {
        delete administrador_resultados_analisis_diario;
    }
}

void IAdministradorScraping::crearAdministradorScrapingLocal()
{
	administrador = new AdministradorScrapingLocal();
    administrador->iniciarDB(ConfiguracionScraping::archivoConfigDBInfoScraping());

    administrador_info = new AdministradorScrapingLocal();
    administrador_info->iniciarDB(ConfiguracionScraping::archivoConfigDBInfoScraping());

    administrador_resultados_analisis_diario = new AdministradorScrapingLocal();
    administrador_resultados_analisis_diario->iniciarDB(ConfiguracionScraping::archivoConfigDBResultadosDiarios());
};

void IAdministradorScraping::crearAdministradorScrapingDistribuido() {};

bool IAdministradorScraping::administradorIniciado()
{
	return administrador != NULL;
}

bool IAdministradorScraping::administradorInfoIniciado()
{
    return administrador_info != NULL;
}

bool IAdministradorScraping::administradorResultadosAnalisisDiarioIniciado()
{
    return administrador_resultados_analisis_diario != NULL;
}
// GETTERS

IAdministradorScraping* IAdministradorScraping::getInstancia()
{
	if (administradorIniciado())
	{
		return administrador;
	}
	else
	{
		throw std::exception("Administrador de aplicacion no inicializado.");
	}
}

IAdministradorScraping* IAdministradorScraping::getInstanciaAdminInfo()
{
    if (administradorInfoIniciado())
    {
        return administrador_info;
    }
    else
    {
        throw std::exception("Administrador de informacion de scraping no inicializado.");
    }
}

IAdministradorScraping* IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()
{
    if (administradorResultadosAnalisisDiarioIniciado())
    {
        return administrador_resultados_analisis_diario;
    }
    else
    {
        throw std::exception("Administrador de resulrados de analisis diarios de scraping no inicializado.");
    }
}

void scraping::IAdministradorScraping::iniciarDB(std::string path_config_db)
{
    almacenamiento::IAdministradorAlmacenamiento::iniciar(path_config_db);

    this->admin_almacenamiento = almacenamiento::IAdministradorAlmacenamiento::getInstancia();
}
