#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping;

// stl
#include <fstream>
#include <sstream>

std::string ConfiguracionScraping::path_config;

bool ConfiguracionScraping::scraping_local;
bool ConfiguracionScraping::scraping_distribuido;
std::string ConfiguracionScraping::prefijo_configuracion;

std::string ConfiguracionScraping::prefijo_medio;
std::string ConfiguracionScraping::prefijo_contenido;
std::string ConfiguracionScraping::prefijo_resultado_medio;
std::string ConfiguracionScraping::prefijo_resultado_contenido;

std::string ConfiguracionScraping::clave_id_medio_actual;
std::string ConfiguracionScraping::clave_id_contenido_actual;

const unsigned int ConfiguracionScraping::tamanio_alocador = 1024;
rapidjson::Document ConfiguracionScraping::documento_alocador;

void ConfiguracionScraping::leerConfiguracion(std::string path_archivo_configuracion)
{
    std::ifstream archivo(path_archivo_configuracion);

    path_config = path_archivo_configuracion;

    if (false == archivo.good())
    {
	    throw - 1;
    }

    std::ostringstream sstream;
    sstream << archivo.rdbuf();
    const std::string string_config(sstream.str());

    rapidjson::Document config_json;
    config_json.Parse(string_config.c_str());

    rapidjson::Value & config_scraping_json = config_json["scraping"];

    scraping_local = config_scraping_json[ConfiguracionScraping::tagScrapingLocal().c_str()].GetBool();
    scraping_distribuido = config_scraping_json[ConfiguracionScraping::tagScrapingDistribuido().c_str()].GetBool();

    prefijo_configuracion = config_scraping_json[ConfiguracionScraping::tagPrefijoConfiguracion().c_str()].GetString();
    prefijo_medio = config_scraping_json[ConfiguracionScraping::tagPrefijoMedio().c_str()].GetString();
    prefijo_contenido = config_scraping_json[ConfiguracionScraping::tagPrefijoContenido().c_str()].GetString();
    prefijo_resultado_medio = config_scraping_json[ConfiguracionScraping::tagPrefijoResultadoMedio().c_str()].GetString();
    prefijo_resultado_contenido = config_scraping_json[ConfiguracionScraping::tagPrefijoResultadoContenido().c_str()].GetString();
}

rapidjson::Document::AllocatorType * ConfiguracionScraping::getAlocador()
{
    return &documento_alocador.GetAllocator();
}

std::string ConfiguracionScraping::pathConfiguracion()
{
    return path_config;
}

bool ConfiguracionScraping::scrapingLocal()
{
    return scraping_local;
}

bool ConfiguracionScraping::scrapingDistribuido()
{
    return scraping_distribuido;
}

std::string ConfiguracionScraping::prefijoConfiguracion()
{
    return prefijo_configuracion;
}

// ENTIDADES
std::string ConfiguracionScraping::prefijoMedio()
{
    return prefijo_medio;
}

std::string ConfiguracionScraping::prefijoContenido()
{
    return prefijo_contenido;
}

std::string ConfiguracionScraping::prefijoResultadoMedio()
{
    return prefijo_resultado_medio;
}

std::string ConfiguracionScraping::prefijoResultadoContenido()
{
    return prefijo_resultado_contenido;
}

std::string ConfiguracionScraping::claveIDMedioActual()
{
    return "id_medio_actual";
}

std::string ConfiguracionScraping::claveIDContenidoActual()
{
    return "id_contenido_actual";
}

std::string ConfiguracionScraping::tagScrapingLocal()
{
    return "scraping_local";
}

std::string ConfiguracionScraping::tagScrapingDistribuido()
{
    return "scraping_distribuido";
}

std::string ConfiguracionScraping::tagPrefijoConfiguracion()
{
    return "prefijo_configuracion";
}

// ENTIDADES
std::string ConfiguracionScraping::tagPrefijoMedio()
{
    return "prefijo_medio";
}

std::string ConfiguracionScraping::tagPrefijoContenido()
{
    return "prefijo_contenido";
}

std::string ConfiguracionScraping::tagPrefijoResultadoMedio()
{
    return "prefijo_resultado_medio";
}

std::string ConfiguracionScraping::tagPrefijoResultadoContenido()
{
    return "prefijo_resultado_contenido";
}

ConfiguracionScraping::ConfiguracionScraping()
{
}

ConfiguracionScraping::~ConfiguracionScraping()
{
}
