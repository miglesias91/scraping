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

std::string ConfiguracionScraping::archivo_config_db_info_temporal;
std::string ConfiguracionScraping::archivo_config_db_resultados_diarios;

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

std::vector<std::string> ConfiguracionScraping::archivos_configs_logs;
std::string ConfiguracionScraping::archivo_config_sentimiento;
std::string ConfiguracionScraping::archivo_config_noticias;
std::string ConfiguracionScraping::path_checkpoint_resultados_diarios;
std::string ConfiguracionScraping::dir_abms;

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

    herramientas::utiles::Json * config_json = nullptr;
    herramientas::utiles::Json * config_scraping_json = nullptr;

    try {
        config_json = new herramientas::utiles::Json(string_config);
        config_scraping_json = config_json->getAtributoValorJson("scraping");

        scraping_local = config_scraping_json->getAtributoValorBool(ConfiguracionScraping::tagScrapingLocal());
        scraping_distribuido = config_scraping_json->getAtributoValorBool(ConfiguracionScraping::tagScrapingDistribuido());

        archivo_config_db_info_temporal = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigDBInfoTemporal());
        archivo_config_db_resultados_diarios = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigDBResultadosDiarios());
        path_checkpoint_resultados_diarios = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagPathCheckpointResultadosDiarios());
        dir_abms = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagDirABMs());

        archivos_configs_logs = config_scraping_json->getAtributoArrayString(ConfiguracionScraping::tagArchivosConfigsLogs());
        archivo_config_sentimiento = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigSentimiento());
        archivo_config_noticias = config_scraping_json->getAtributoValorString(ConfiguracionScraping::tagArchivoConfigNoticias());

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

std::string ConfiguracionScraping::archivoConfigDBInfoTemporal()
{
    return archivo_config_db_info_temporal;
}

std::string ConfiguracionScraping::archivoConfigDBResultadosDiarios()
{
    return archivo_config_db_resultados_diarios;
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

std::vector<std::string> ConfiguracionScraping::archivosConfigsLogs()
{
    return archivos_configs_logs;
}

std::string ConfiguracionScraping::archivoConfigSentimiento()
{
    return archivo_config_sentimiento;
}

std::string ConfiguracionScraping::archivoConfigNoticias()
{
    return archivo_config_noticias;
}

std::string scraping::ConfiguracionScraping::pathCheckpointResultadosDiarios() {
    return path_checkpoint_resultados_diarios;
}

std::string scraping::ConfiguracionScraping::dirABMs() {
    return dir_abms;
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
    return "db_resultados_diarios";
}

std::string ConfiguracionScraping::tagPathCheckpointResultadosDiarios() {
    return "path_checkpoint_resultados_diarios";
}

std::string ConfiguracionScraping::tagDirABMs() {
    return "dir_abms";
}

std::string ConfiguracionScraping::tagArchivoConfigDBInfoTemporal()
{
    return "db_info_temporal";
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

std::string ConfiguracionScraping::tagArchivosConfigsLogs()
{
    return "logs";
}

std::string ConfiguracionScraping::tagArchivoConfigSentimiento()
{
    return "config_sentimiento";
}

std::string ConfiguracionScraping::tagArchivoConfigNoticias()
{
    return "config_noticias";
}

ConfiguracionScraping::ConfiguracionScraping()
{
}

ConfiguracionScraping::~ConfiguracionScraping()
{
}
