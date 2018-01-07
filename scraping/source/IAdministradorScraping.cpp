#include <scraping/include/IAdministradorScraping.h>

using namespace scraping;

// stl
#include <iostream>

// aplicacion
#include <scraping/include/AdministradorScrapingLocal.h>
#include <scraping/include/ConfiguracionScraping.h>

typedef scraping::IAdministradorScraping* (*admin)();

IAdministradorScraping* IAdministradorScraping::administrador = NULL;

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
}

void IAdministradorScraping::crearAdministradorScrapingLocal()
{
	administrador = new AdministradorScrapingLocal();
};

void IAdministradorScraping::crearAdministradorScrapingDistribuido() {};


bool IAdministradorScraping::administradorIniciado()
{
	return administrador != NULL;
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
