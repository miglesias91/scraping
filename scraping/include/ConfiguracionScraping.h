#pragma once

// stl
#include <string>

namespace scraping
{

class ConfiguracionScraping
{
public:

    static void leerConfiguracion(std::string path_archivo_configuracion);

    // CONFIGURACIONES

    static std::string pathConfiguracion();

    static bool scrapingLocal();
    static bool scrapingDistribuido();

    static std::string archivoConfigDBInfoScraping();
    static std::string archivoConfigDBResultadosDiarios();

    static std::string prefijoConfiguracion();

    static std::string prefijoTwitter();
    static std::string prefijoHTML();
    static std::string prefijoFacebook();
    static std::string prefijoRSS();

    static std::string prefijoMedio();
    static std::string prefijoContenido();

    static std::string prefijoResultadoMedio();
    static std::string prefijoResultadoContenido();
    static std::string prefijoResultadoDiario();

    static std::string claveIDMedioActual();
    static std::string claveIDContenidoActual();

    static std::string archivoConfigLog();

    // TAGS

    static std::string tagScrapingLocal();
    static std::string tagScrapingDistribuido();

    static std::string tagArchivoConfigDBInfoScraping();
    static std::string tagArchivoConfigDBResultadosDiarios();

    static std::string tagPrefijoConfiguracion();

    static std::string tagPrefijoTwitter();
    static std::string tagPrefijoHTML();
    static std::string tagPrefijoFacebook();
    static std::string tagPrefijoRSS();

    static std::string tagPrefijoMedio();
    static std::string tagPrefijoContenido();

    static std::string tagPrefijoResultadoMedio();
    static std::string tagPrefijoResultadoContenido();
    static std::string tagPrefijoResultadoDiario();

    static std::string tagArchivoConfigLog();

private:

    ConfiguracionScraping();
    virtual ~ConfiguracionScraping();

    static std::string path_config;

    static std::string archivo_config_db_resultados_analisis_diario;
    static std::string archivo_config_db_info_scraping;

    static bool scraping_local;
    static bool scraping_distribuido;
    static std::string prefijo_configuracion;

    static std::string prefijo_twitter;
    static std::string prefijo_html;
    static std::string prefijo_facebook;
    static std::string prefijo_rss;

    static std::string prefijo_medio;
    static std::string prefijo_contenido;
    static std::string prefijo_resultado_medio;
    static std::string prefijo_resultado_contenido;
    static std::string prefijo_resultado_diario;

    static std::string clave_id_medio_actual;
    static std::string clave_id_contenido_actual;

    static std::string archivo_config_log;

};

};

