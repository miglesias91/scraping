#pragma once

// stl
#include <string>

// rapidjson
#include <rapidjson/document.h>

namespace scraping
{

class ConfiguracionScraping
{
public:

    static void leerConfiguracion(std::string path_archivo_configuracion);

    // METODOS

    static rapidjson::Document::AllocatorType * getAlocador();

    // CONFIGURACIONES

    static std::string pathConfiguracion();

    static bool scrapingLocal();
    static bool scrapingDistribuido();
    static std::string prefijoConfiguracion();

    static std::string prefijoMedio();
    static std::string prefijoContenido();

    static std::string prefijoResultadoMedio();
    static std::string prefijoResultadoContenido();
    static std::string prefijoResultadoDiario();

    static std::string claveIDMedioActual();
    static std::string claveIDContenidoActual();

    // TAGS

    static std::string tagScrapingLocal();
    static std::string tagScrapingDistribuido();
    static std::string tagPrefijoConfiguracion();

    static std::string tagPrefijoMedio();
    static std::string tagPrefijoContenido();

    static std::string tagPrefijoResultadoMedio();
    static std::string tagPrefijoResultadoContenido();
    static std::string tagPrefijoResultadoDiario();

private:

    ConfiguracionScraping();
    virtual ~ConfiguracionScraping();

    static std::string path_config;

    static bool scraping_local;
    static bool scraping_distribuido;
    static std::string prefijo_configuracion;

    static std::string prefijo_medio;
    static std::string prefijo_contenido;
    static std::string prefijo_resultado_medio;
    static std::string prefijo_resultado_contenido;
    static std::string prefijo_resultado_diario;

    static std::string clave_id_medio_actual;
    static std::string clave_id_contenido_actual;

    static const unsigned int tamanio_alocador;

    static rapidjson::Document documento_alocador;
};

};

