#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping;

// stl
#include <fstream>
#include <sstream>

std::string ConfiguracionScraping::path_config;

bool ConfiguracionScraping::scraping_local;
bool ConfiguracionScraping::scraping_distribuido;

std::string ConfiguracionScraping::archivo_config_db_info_scraping;
std::string ConfiguracionScraping::archivo_config_db_resultados_analisis_diario;

std::string ConfiguracionScraping::prefijo_configuracion;

std::string ConfiguracionScraping::prefijo_twitter;
std::string ConfiguracionScraping::prefijo_html;
std::string ConfiguracionScraping::prefijo_facebook;
std::string ConfiguracionScraping::prefijo_rss;

std::string ConfiguracionScraping::prefijo_medio;
std::string ConfiguracionScraping::prefijo_contenido;
std::string ConfiguracionScraping::prefijo_resultado_medio;
std::string ConfiguracionScraping::prefijo_resultado_contenido;
std::string ConfiguracionScraping::prefijo_resultado_diario;

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

    archivo_config_db_info_scraping = config_scraping_json[ConfiguracionScraping::tagArchivoConfigDBInfoScraping().c_str()].GetString();
    archivo_config_db_resultados_analisis_diario = config_scraping_json[ConfiguracionScraping::tagArchivoConfigDBResultadosDiarios().c_str()].GetString();

    prefijo_configuracion = config_scraping_json[ConfiguracionScraping::tagPrefijoConfiguracion().c_str()].GetString();

    prefijo_twitter = config_scraping_json[ConfiguracionScraping::tagPrefijoTwitter().c_str()].GetString();
    prefijo_html = config_scraping_json[ConfiguracionScraping::tagPrefijoHTML().c_str()].GetString();
    prefijo_facebook = config_scraping_json[ConfiguracionScraping::tagPrefijoFacebook().c_str()].GetString();
    prefijo_rss = config_scraping_json[ConfiguracionScraping::tagPrefijoRSS().c_str()].GetString();

    prefijo_medio = config_scraping_json[ConfiguracionScraping::tagPrefijoMedio().c_str()].GetString();
    prefijo_contenido = config_scraping_json[ConfiguracionScraping::tagPrefijoContenido().c_str()].GetString();
    
    prefijo_resultado_medio = config_scraping_json[ConfiguracionScraping::tagPrefijoResultadoMedio().c_str()].GetString();
    prefijo_resultado_contenido = config_scraping_json[ConfiguracionScraping::tagPrefijoResultadoContenido().c_str()].GetString();
    prefijo_resultado_diario = config_scraping_json[ConfiguracionScraping::tagPrefijoResultadoDiario().c_str()].GetString();
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

std::string ConfiguracionScraping::archivoConfigDBInfoScraping()
{
    return archivo_config_db_info_scraping;
}

std::string ConfiguracionScraping::archivoConfigDBResultadosDiarios()
{
    return archivo_config_db_resultados_analisis_diario;
}

std::string ConfiguracionScraping::prefijoConfiguracion()
{
    return prefijo_configuracion;
}

std::string ConfiguracionScraping::prefijoTwitter()
{
    return prefijo_twitter;
}

std::string ConfiguracionScraping::prefijoHTML()
{
    return prefijo_html;
}

std::string ConfiguracionScraping::prefijoFacebook()
{
    return prefijo_facebook;
}

std::string ConfiguracionScraping::prefijoRSS()
{
    return prefijo_rss;
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

std::string ConfiguracionScraping::prefijoResultadoDiario()
{
    return prefijo_resultado_diario;
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

std::string ConfiguracionScraping::tagArchivoConfigDBResultadosDiarios()
{
    return "config_db_resultados_analisis_diario";
}

std::string ConfiguracionScraping::tagArchivoConfigDBInfoScraping()
{
    return "config_db_info_scraping";
}

std::string ConfiguracionScraping::tagPrefijoConfiguracion()
{
    return "prefijo_configuracion";
}

std::string ConfiguracionScraping::tagPrefijoTwitter()
{
    return "prefijo_twitter";
}

std::string ConfiguracionScraping::tagPrefijoHTML()
{
    return "prefijo_html";
}

std::string ConfiguracionScraping::tagPrefijoFacebook()
{
    return "prefijo_facebook";
}

std::string ConfiguracionScraping::tagPrefijoRSS()
{
    return "prefijo_rss";
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

std::string ConfiguracionScraping::tagPrefijoResultadoDiario()
{
    return "prefijo_resultado_diario";
}

ConfiguracionScraping::ConfiguracionScraping()
{
}

ConfiguracionScraping::~ConfiguracionScraping()
{
}
