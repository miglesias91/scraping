#include <scraping/include/ConfiguracionScraping.h>

// stl
#include <fstream>
#include <sstream>

// utiles
#include <utiles/include/Json.h>
#include <utiles/include/ImposibleAbrirArchivo.h>

using namespace scraping;

std::string ConfiguracionScraping::path_config;

bool ConfiguracionScraping::scraping_local;
bool ConfiguracionScraping::scraping_distribuido;

std::string ConfiguracionScraping::archivo_config_db_info_scraping;
std::string ConfiguracionScraping::archivo_config_db_resultados_analisis_diario;

std::string ConfiguracionScraping::prefijo_configuracion;

std::string ConfiguracionScraping::prefijo_twitter;
std::string ConfiguracionScraping::prefijo_portal_noticias;
std::string ConfiguracionScraping::prefijo_facebook;
std::string ConfiguracionScraping::prefijo_rss;

std::string ConfiguracionScraping::prefijo_medio;
std::string ConfiguracionScraping::prefijo_contenido;
std::string ConfiguracionScraping::prefijo_contenido_depurado;
std::string ConfiguracionScraping::prefijo_resultado_medio;
std::string ConfiguracionScraping::prefijo_resultado_contenido;
std::string ConfiguracionScraping::prefijo_resultado_diario;

std::string ConfiguracionScraping::clave_id_medio_actual;
std::string ConfiguracionScraping::clave_id_contenido_actual;

std::string ConfiguracionScraping::archivo_config_log;
std::string ConfiguracionScraping::archivo_config_sentimiento;

void ConfiguracionScraping::leerConfiguracion(std::string path_archivo_configuracion)
{
    std::ifstream archivo(path_archivo_configuracion);

    path_config = path_archivo_configuracion;

    if (false == archivo.good()) {
	    throw herramientas::utiles::excepciones::ImposibleAbrirArchivo(path_archivo_configuracion);
    }

    std::ostringstream sstream;
    sstream << archivo.rdbuf();
    const std::string string_config(sstream.str());

    herramientas::utiles::Json * config_json = NULL;
    herramientas::utiles::Json * config_scraping_json = NULL;

    try {
        config_json = new herramientas::utiles::Json(string_config);
        config_scraping_json = config_json->getAtributoValorJson("scraping");

        scraping_local = config_scraping_json->getAtributoValorBool(ConfiguracionScraping::tagScrapingLocal());
        scraping_distribuido = config_scraping_json->getAtributoValorBool(ConfiguracionScraping::tagScrapingDistribuido());

        archivo_config_db_info_scraping = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigDBInfoScraping());
        archivo_config_db_resultados_analisis_diario = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigDBResultadosDiarios());

        archivo_config_log = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigLog());
        archivo_config_sentimiento = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigSentimiento());

        prefijo_configuracion = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoConfiguracion());

        prefijo_twitter = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoTwitter());
        prefijo_portal_noticias = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoPortalNoticias());
        prefijo_facebook = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoFacebook());
        prefijo_rss = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoRSS());

        prefijo_medio = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoMedio());
        prefijo_contenido = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoContenido());
        prefijo_contenido_depurado = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoContenidoDepurado());

        prefijo_resultado_medio = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoResultadoMedio());
        prefijo_resultado_contenido = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoResultadoContenido());
        prefijo_resultado_diario = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPrefijoResultadoDiario());
    }
    catch (herramientas::utiles::excepciones::Excepcion & e) {
        delete config_scraping_json;
        delete config_json;

        throw;
    }

    delete config_scraping_json;
    delete config_json;
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

std::string ConfiguracionScraping::prefijoPortalNoticias()
{
    return prefijo_portal_noticias;
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

std::string ConfiguracionScraping::prefijoContenidoDepurado()
{
    return prefijo_contenido_depurado;
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

std::string ConfiguracionScraping::archivoConfigLog()
{
    return archivo_config_log;
}

std::string ConfiguracionScraping::archivoConfigSentimiento()
{
    return archivo_config_sentimiento;
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
    return "db_resultados_analisis_diario";
}

std::string ConfiguracionScraping::tagArchivoConfigDBInfoScraping()
{
    return "db_info_scraping";
}

std::string ConfiguracionScraping::tagPrefijoConfiguracion()
{
    return "prefijo_configuracion";
}

std::string ConfiguracionScraping::tagPrefijoTwitter()
{
    return "prefijo_twitter";
}

std::string ConfiguracionScraping::tagPrefijoPortalNoticias()
{
    return "prefijo_portal_noticias";
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

std::string ConfiguracionScraping::tagPrefijoContenidoDepurado()
{
    return "prefijo_contenido_depurado";
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

std::string ConfiguracionScraping::tagArchivoConfigLog()
{
    return "log_scraping";
}

std::string ConfiguracionScraping::tagArchivoConfigSentimiento()
{
    return "config_sentimiento";
}

ConfiguracionScraping::ConfiguracionScraping()
{
}

ConfiguracionScraping::~ConfiguracionScraping()
{
}
