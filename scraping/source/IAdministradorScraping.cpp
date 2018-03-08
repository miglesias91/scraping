#include <scraping/include/IAdministradorScraping.h>

using namespace scraping;

// stl
#include <iostream>

// aplicacion
#include <scraping/include/AdministradorScrapingLocal.h>
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/ScrapingIniciadoPreviamente.h>
#include <scraping/include/ScrapingNoInicializado.h>

// extraccion
#include <extraccion/include/Medio.h>
#include <extraccion/include/Contenido.h>

typedef scraping::IAdministradorScraping* (*admin)();

IAdministradorScraping* IAdministradorScraping::administrador_info = NULL;
IAdministradorScraping* IAdministradorScraping::administrador_resultados_analisis_diario = NULL;

IAdministradorScraping::IAdministradorScraping() : admin_almacenamiento(NULL), handler_almacenamiento(0)
{
}

IAdministradorScraping::~IAdministradorScraping()
{
}

void IAdministradorScraping::iniciar(std::string path_configuracion)
{
    if (administradorInfoIniciado() || administradorResultadosAnalisisDiarioIniciado())
    {
        throw excepciones::ScrapingIniciadoPreviamente();
    }

    try
    {
        ConfiguracionScraping::leerConfiguracion(path_configuracion);
    }
    catch (herramientas::utiles::excepciones::Excepcion & e)
    {
        throw;
    }

    Logger::iniciar(ConfiguracionScraping::archivoConfigLog());

    Logger::marca("INICIO SCRAPING");

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
    if (true == administradorInfoIniciado())
    {
        delete administrador_info;
    }

    if (true == administradorResultadosAnalisisDiarioIniciado())
    {
        delete administrador_resultados_analisis_diario;
    }

    Logger::marca("FIN SCRAPING");

    //herramientas::log::AdministradorLog::liberarTodo();
}

void IAdministradorScraping::crearAdministradorScrapingLocal()
{
    Logger::info("iniciando admin info scraping.");

    administrador_info = new AdministradorScrapingLocal();
    administrador_info->iniciarDB(ConfiguracionScraping::archivoConfigDBInfoScraping());

    Logger::info("iniciando admin resultados scraping.");

    administrador_resultados_analisis_diario = new AdministradorScrapingLocal();
    administrador_resultados_analisis_diario->iniciarDB(ConfiguracionScraping::archivoConfigDBResultadosDiarios());
};

void IAdministradorScraping::crearAdministradorScrapingDistribuido() {};

bool IAdministradorScraping::administradorInfoIniciado()
{
    return administrador_info != NULL;
}

bool IAdministradorScraping::administradorResultadosAnalisisDiarioIniciado()
{
    return administrador_resultados_analisis_diario != NULL;
}
// GETTERS

IAdministradorScraping* IAdministradorScraping::getInstanciaAdminInfo()
{
    if (administradorInfoIniciado())
    {
        return administrador_info;
    }
    else
    {
        throw excepciones::ScrapingNoInicializado("admin info");
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
        throw excepciones::ScrapingNoInicializado("admin resultados");
    }
}

void scraping::IAdministradorScraping::recuperarIDsActuales()
{
    unsigned long long int id_actual_medio = this->recuperarIDActual<scraping::extraccion::Medio>();
    unsigned long long int id_actual_contenido = this->recuperarIDActual<scraping::extraccion::Contenido>();

    scraping::extraccion::Medio::getGestorIDs()->setIdActual(id_actual_medio);
    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(id_actual_contenido);
}

void scraping::IAdministradorScraping::almacenarIDsActuales()
{
    unsigned long long int id_actual_medio = scraping::extraccion::Medio::getGestorIDs()->getIdActual();
    unsigned long long int id_actual_contenido = scraping::extraccion::Contenido::getGestorIDs()->getIdActual();

    this->almacenarIDActual<scraping::extraccion::Medio>();
    this->almacenarIDActual<scraping::extraccion::Contenido>();

    Logger::info("id actuales almacenados: id_actual_medio = " + std::to_string(id_actual_medio) + " - id_actual_contenido = " + std::to_string(id_actual_contenido) + ".");
}

void scraping::IAdministradorScraping::iniciarDB(std::string path_config_db)
{ 
    this->handler_almacenamiento = almacenamiento::IAdministradorAlmacenamiento::iniciarNuevo(path_config_db);
    this->admin_almacenamiento = almacenamiento::IAdministradorAlmacenamiento::getInstancia(this->handler_almacenamiento);
}
