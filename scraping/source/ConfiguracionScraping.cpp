#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping;

// stl
#include <fstream>
#include <sstream>

std::string ConfiguracionScraping::path_config;

bool ConfiguracionScraping::aplicacion_local;
bool ConfiguracionScraping::aplicacion_distribuida;
bool ConfiguracionScraping::prefijo_habilitado;
unsigned int ConfiguracionScraping::prefijo_tamanio;
std::string ConfiguracionScraping::prefijo_configuracion;

std::string ConfiguracionScraping::prefijo_concepto;
std::string ConfiguracionScraping::prefijo_termino;
std::string ConfiguracionScraping::prefijo_consulta;
std::string ConfiguracionScraping::prefijo_reporte;
std::string ConfiguracionScraping::prefijo_seccion;
std::string ConfiguracionScraping::prefijo_periodo;
std::string ConfiguracionScraping::prefijo_fecha;
std::string ConfiguracionScraping::prefijo_medio;

std::string ConfiguracionScraping::prefijo_relaciones_concepto;
std::string ConfiguracionScraping::prefijo_relaciones_termino;
std::string ConfiguracionScraping::prefijo_relaciones_consulta;
std::string ConfiguracionScraping::prefijo_relaciones_reporte;
std::string ConfiguracionScraping::prefijo_relaciones_seccion;
std::string ConfiguracionScraping::prefijo_relaciones_periodo;
std::string ConfiguracionScraping::prefijo_relaciones_fecha;
std::string ConfiguracionScraping::prefijo_relaciones_medio;

std::string ConfiguracionScraping::clave_id_actual;

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

    rapidjson::Value & config_app_json = config_json["aplicacion"];

	aplicacion_local = config_app_json[ConfiguracionScraping::tagAplicacionLocal().c_str()].GetBool();
	aplicacion_distribuida = config_app_json[ConfiguracionScraping::tagAplicacionDistribuida().c_str()].GetBool();
	prefijo_habilitado = config_app_json[ConfiguracionScraping::tagPrefijoHabilitado().c_str()].GetBool();
	prefijo_tamanio = config_app_json[ConfiguracionScraping::tagPrefijoTamanio().c_str()].GetUint();

	prefijo_configuracion = config_app_json[ConfiguracionScraping::tagPrefijoConfiguracion().c_str()].GetString();
	prefijo_concepto = config_app_json[ConfiguracionScraping::tagPrefijoConcepto().c_str()].GetString();
	prefijo_termino = config_app_json[ConfiguracionScraping::tagPrefijoTermino().c_str()].GetString();
	prefijo_consulta = config_app_json[ConfiguracionScraping::tagPrefijoConsulta().c_str()].GetString();
	prefijo_reporte = config_app_json[ConfiguracionScraping::tagPrefijoReporte().c_str()].GetString();
	prefijo_seccion = config_app_json[ConfiguracionScraping::tagPrefijoSeccion().c_str()].GetString();
	prefijo_periodo = config_app_json[ConfiguracionScraping::tagPrefijoPeriodo().c_str()].GetString();
	prefijo_fecha = config_app_json[ConfiguracionScraping::tagPrefijoFecha().c_str()].GetString();
	prefijo_medio = config_app_json[ConfiguracionScraping::tagPrefijoMedio().c_str()].GetString();

    prefijo_relaciones_concepto = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesConcepto().c_str()].GetString();
    prefijo_relaciones_termino = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesTermino().c_str()].GetString();
    prefijo_relaciones_consulta = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesConsulta().c_str()].GetString();
    prefijo_relaciones_reporte = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesReporte().c_str()].GetString();
    prefijo_relaciones_seccion = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesSeccion().c_str()].GetString();
    prefijo_relaciones_periodo = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesPeriodo().c_str()].GetString();
    prefijo_relaciones_fecha = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesFecha().c_str()].GetString();
    prefijo_relaciones_medio = config_app_json[ConfiguracionScraping::tagPrefijoRelacionesMedio().c_str()].GetString();

	// recorto el prefijo al tamanio indicado en el archivo de config.
	prefijo_configuracion.erase(prefijo_configuracion.begin() + prefijo_tamanio, prefijo_configuracion.end());
	prefijo_concepto.erase(prefijo_concepto.begin() + prefijo_tamanio, prefijo_concepto.end());
	prefijo_termino.erase(prefijo_termino.begin() + prefijo_tamanio, prefijo_termino.end());
	prefijo_consulta.erase(prefijo_consulta.begin() + prefijo_tamanio, prefijo_consulta.end());
	prefijo_reporte.erase(prefijo_reporte.begin() + prefijo_tamanio, prefijo_reporte.end());
	prefijo_seccion.erase(prefijo_seccion.begin() + prefijo_tamanio, prefijo_seccion.end());
	prefijo_fecha.erase(prefijo_fecha.begin() + prefijo_tamanio, prefijo_fecha.end());
	prefijo_medio.erase(prefijo_medio.begin() + prefijo_tamanio, prefijo_medio.end());

    prefijo_relaciones_concepto.erase(prefijo_relaciones_concepto.begin() + prefijo_tamanio, prefijo_relaciones_concepto.end());
    prefijo_relaciones_termino.erase(prefijo_relaciones_termino.begin() + prefijo_tamanio, prefijo_relaciones_termino.end());
    prefijo_relaciones_consulta.erase(prefijo_relaciones_consulta.begin() + prefijo_tamanio, prefijo_relaciones_consulta.end());
    prefijo_relaciones_reporte.erase(prefijo_relaciones_reporte.begin() + prefijo_tamanio, prefijo_relaciones_reporte.end());
    prefijo_relaciones_seccion.erase(prefijo_relaciones_seccion.begin() + prefijo_tamanio, prefijo_relaciones_seccion.end());
    prefijo_relaciones_fecha.erase(prefijo_relaciones_fecha.begin() + prefijo_tamanio, prefijo_relaciones_fecha.end());
    prefijo_relaciones_medio.erase(prefijo_relaciones_medio.begin() + prefijo_tamanio, prefijo_relaciones_medio.end());
}

rapidjson::Document::AllocatorType * ConfiguracionScraping::getAlocador()
{
	return &documento_alocador.GetAllocator();
}

std::string ConfiguracionScraping::pathConfiguracion()
{
    return path_config;
}

bool ConfiguracionScraping::aplicacionLocal()
{
	return aplicacion_local;
}

bool ConfiguracionScraping::aplicacionDistribuida()
{
	return aplicacion_distribuida;
}

bool ConfiguracionScraping::prefijoHabilitado()
{
	return prefijo_habilitado;
}

unsigned int ConfiguracionScraping::prefijoTamanio()
{
	return prefijo_tamanio;
}

std::string ConfiguracionScraping::prefijoConfiguracion()
{
	return prefijo_configuracion;
}

// ENTIDADES
std::string ConfiguracionScraping::prefijoConcepto()
{
	return prefijo_concepto;
}

std::string ConfiguracionScraping::prefijoTermino()
{
	return prefijo_termino;
}

std::string ConfiguracionScraping::prefijoConsulta()
{
	return prefijo_consulta;
}

std::string ConfiguracionScraping::prefijoReporte()
{
	return prefijo_reporte;
}

std::string ConfiguracionScraping::prefijoSeccion()
{
	return prefijo_seccion;
}

std::string ConfiguracionScraping::prefijoPeriodo()
{
	return prefijo_periodo;
}

std::string ConfiguracionScraping::prefijoFecha()
{
	return prefijo_fecha;
}

std::string ConfiguracionScraping::prefijoMedio()
{
	return prefijo_medio;
}

// relaciones
std::string ConfiguracionScraping::prefijoRelacionesConcepto()
{
    return prefijo_relaciones_concepto;
}

std::string ConfiguracionScraping::prefijoRelacionesTermino()
{
    return prefijo_relaciones_termino;
}

std::string ConfiguracionScraping::prefijoRelacionesConsulta()
{
    return prefijo_relaciones_consulta;
}

std::string ConfiguracionScraping::prefijoRelacionesReporte()
{
    return prefijo_relaciones_reporte;
}

std::string ConfiguracionScraping::prefijoRelacionesSeccion()
{
    return prefijo_relaciones_seccion;
}

std::string ConfiguracionScraping::prefijoRelacionesPeriodo()
{
    return prefijo_relaciones_periodo;
}

std::string ConfiguracionScraping::prefijoRelacionesFecha()
{
    return prefijo_relaciones_fecha;
}

std::string ConfiguracionScraping::prefijoRelacionesMedio()
{
    return prefijo_relaciones_medio;
}

std::string ConfiguracionScraping::claveIDActual()
{
	return "id_actual";
}

std::string ConfiguracionScraping::tagAplicacionLocal()
{
	return "aplicacion_local";
}

std::string ConfiguracionScraping::tagAplicacionDistribuida()
{
	return "aplicacion_distribuida";
}

std::string ConfiguracionScraping::tagPrefijoHabilitado()
{
	return "prefijo_habilitado";
}

std::string ConfiguracionScraping::tagPrefijoTamanio()
{
	return "prefijo_tamanio";
}

std::string ConfiguracionScraping::tagPrefijoConfiguracion()
{
	return "prefijo_configuracion";
}

// ENTIDADES
std::string ConfiguracionScraping::tagPrefijoConcepto()
{
	return "prefijo_concepto";
}

std::string ConfiguracionScraping::tagPrefijoTermino()
{
	return "prefijo_termino";
}

std::string ConfiguracionScraping::tagPrefijoConsulta()
{
	return "prefijo_consulta";
}

std::string ConfiguracionScraping::tagPrefijoReporte()
{
	return "prefijo_reporte";
}

std::string ConfiguracionScraping::tagPrefijoSeccion()
{
	return "prefijo_seccion";
}

std::string ConfiguracionScraping::tagPrefijoPeriodo()
{
	return "prefijo_periodo";
}

std::string ConfiguracionScraping::tagPrefijoFecha()
{
	return "prefijo_fecha";
}

std::string ConfiguracionScraping::tagPrefijoMedio()
{
	return "prefijo_medio";
}

// RELACIONES
std::string ConfiguracionScraping::tagPrefijoRelacionesConcepto()
{
    return "prefijo_relaciones_concepto";
}

std::string ConfiguracionScraping::tagPrefijoRelacionesTermino()
{
    return "prefijo_relaciones_termino";
}

std::string ConfiguracionScraping::tagPrefijoRelacionesConsulta()
{
    return "prefijo_relaciones_consulta";
}

std::string ConfiguracionScraping::tagPrefijoRelacionesReporte()
{
    return "prefijo_relaciones_reporte";
}

std::string ConfiguracionScraping::tagPrefijoRelacionesSeccion()
{
    return "prefijo_relaciones_seccion";
}

std::string ConfiguracionScraping::tagPrefijoRelacionesPeriodo()
{
    return "prefijo_relaciones_periodo";
}

std::string ConfiguracionScraping::tagPrefijoRelacionesFecha()
{
    return "prefijo_relaciones_fecha";
}

std::string ConfiguracionScraping::tagPrefijoRelacionesMedio()
{
    return "prefijo_relaciones_medio";
}

ConfiguracionScraping::ConfiguracionScraping()
{
}

ConfiguracionScraping::~ConfiguracionScraping()
{
}
