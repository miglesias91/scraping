#include <scraping/include/IAdministradorScraping.h>

using namespace scraping;

// windows
//#include <winhttp.h>
#include <WinInet.h>

// stl
#include <iostream>

// medios
#include <noticias/include/config.h>

// aplicacion
#include <scraping/include/AdministradorScrapingLocal.h>
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/ScrapingIniciadoPreviamente.h>
#include <scraping/include/ScrapingNoInicializado.h>

// extraccion
#include <extraccion/include/Medio.h>
#include <extraccion/include/Contenido.h>

// depuracion
#include <depuracion/include/Depurador.h>

// analisis
#include <analisis/include/Sentimiento.h>

typedef scraping::IAdministradorScraping* (*admin)();

IAdministradorScraping* IAdministradorScraping::administrador_info_temporal = nullptr;
IAdministradorScraping* IAdministradorScraping::administrador_resultados_diarios = nullptr;

IAdministradorScraping::IAdministradorScraping() : admin_almacenamiento(nullptr), handler_almacenamiento(0) {}

IAdministradorScraping::~IAdministradorScraping() {}

void IAdministradorScraping::iniciar(std::string path_configuracion)
{
    if (false == chequear_conexiones()) {
        Logger::error("NO HAY CONEXION A INTERNET.");
        return;
    }

    if (administradorInfoTemporalIniciado() || administradorResultadosDiariosIniciado())
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

    depuracion::Depurador::cargarStopwords("stopwords_espaniol.txt");
    depuracion::Depurador::cargarMapeoUTF8("mapeo_utf8.csv");

    analisis::tecnicas::Sentimiento::cargar(ConfiguracionScraping::archivoConfigSentimiento());

    medios::noticias::config::levantar(ConfiguracionScraping::archivoConfigNoticias());

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
    if (true == administradorInfoTemporalIniciado())
    {
        delete administrador_info_temporal;
    }

    if (true == administradorResultadosDiariosIniciado())
    {
        delete administrador_resultados_diarios;
    }

    depuracion::Depurador::liberarMapeoUTF8();

    Logger::marca("FIN SCRAPING");

    herramientas::log::AdministradorLog::liberarTodo();
}

void IAdministradorScraping::crearAdministradorScrapingLocal()
{
    Logger::info("iniciando admin info scraping.");

    administrador_info_temporal = new AdministradorScrapingLocal();
    administrador_info_temporal->iniciarDB(ConfiguracionScraping::archivoConfigDBInfoTemporal());

    Logger::info("iniciando admin resultados scraping.");

    administrador_resultados_diarios = new AdministradorScrapingLocal();
    administrador_resultados_diarios->iniciarDB(ConfiguracionScraping::archivoConfigDBResultadosDiarios());
};

void IAdministradorScraping::crearAdministradorScrapingDistribuido() {};

bool IAdministradorScraping::administradorInfoTemporalIniciado()
{
    return administrador_info_temporal != nullptr;
}

bool IAdministradorScraping::administradorResultadosDiariosIniciado()
{
    return administrador_resultados_diarios != nullptr;
}
// GETTERS

IAdministradorScraping* IAdministradorScraping::getInstanciaAdminInfoTemporal()
{
    if (administradorInfoTemporalIniciado())
    {
        return administrador_info_temporal;
    }
    else
    {
        throw excepciones::ScrapingNoInicializado("admin info temporal");
    }
}

IAdministradorScraping* IAdministradorScraping::getInstanciaAdminResultadosDiarios()
{
    if (administradorResultadosDiariosIniciado())
    {
        return administrador_resultados_diarios;
    }
    else
    {
        throw excepciones::ScrapingNoInicializado("admin resultados diarios");
    }
}

bool IAdministradorScraping::guardar_checkpoint() {

    std::string path_checkpoint = ConfiguracionScraping::dirCheckpointResultadosDiarios() + "/" + herramientas::utiles::Fecha::getFechaActual().getStringAAAAMMDDHHmmSS();
    return this->admin_almacenamiento->checkpoint(path_checkpoint);
}

void scraping::IAdministradorScraping::recuperarIDsActuales()
{
    uintmax_t id_actual_medio = this->recuperarIDActual<scraping::extraccion::Medio>();
    uintmax_t id_actual_contenido = this->recuperarIDActual<scraping::extraccion::Contenido>();

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

bool IAdministradorScraping::chequear_conexiones() {
    if(false == InternetCheckConnection(L"http://www.google.com",FLAG_ICC_FORCE_CONNECTION,0))
    {
        return false;
    }
    if(false == InternetCheckConnection(L"http://www.twitter.com",FLAG_ICC_FORCE_CONNECTION,0))
    {
        return false;
    }
    if(false == InternetCheckConnection(L"http://www.facebook.com",FLAG_ICC_FORCE_CONNECTION,0))
    {
        return false;
    }
    if(false == InternetCheckConnection(L"http://www.clarin.com",FLAG_ICC_FORCE_CONNECTION,0))
    {
        return false;
    }
    if(false == InternetCheckConnection(L"http://www.infobae.com",FLAG_ICC_FORCE_CONNECTION,0))
    {
        return false;
    }
    if(false == InternetCheckConnection(L"http://www.lanacion.com.ar",FLAG_ICC_FORCE_CONNECTION,0))
    {
        return false;
    }
    if(false == InternetCheckConnection(L"http://www.pagina12.com.ar",FLAG_ICC_FORCE_CONNECTION,0))
    {
        return false;
    }
    return true;
}
