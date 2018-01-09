#include <analisis/include/ResultadoAnalisis.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::analisis;

ResultadoAnalisis::ResultadoAnalisis(tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia) : IAlmacenable(ConfiguracionScraping::prefijoResultado()), IContieneJson(), resultado_fuerza_en_noticia(resultado_fuerza_en_noticia)
{
}

ResultadoAnalisis::~ResultadoAnalisis()
{
    if (NULL != this->resultado_fuerza_en_noticia)
    {
        delete this->resultado_fuerza_en_noticia;
        this->resultado_fuerza_en_noticia = NULL;
    }
}

// GETTERS

tecnicas::ResultadoFuerzaEnNoticia * ResultadoAnalisis::getResultadoFuerzaEnNoticia()
{
    return this->resultado_fuerza_en_noticia;
}

// getters de IAlmacenable

std::string ResultadoAnalisis::getValorAlmacenable()
{
    this->armarJson();

    return this->getJson()->jsonString();
}

bool ResultadoAnalisis::armarJson()
{
    this->getJson()->reset();
    
    this->resultado_fuerza_en_noticia->armarJson();

    this->getJson()->agregarAtributoJson("fuerza_en_noticia", this->resultado_fuerza_en_noticia->getJson());

    return true;
}

// SETTERS

// METODOS


// metodos de IContieneJson

bool ResultadoAnalisis::parsearJson()
{
    herramientas::utiles::Json * json_fuerza_en_noticia = this->getJson()->getAtributoValorJson("fuerza_en_noticia");

    this->resultado_fuerza_en_noticia->setJson(json_fuerza_en_noticia);
    this->resultado_fuerza_en_noticia->parsearJson();

    return true;
}

void ResultadoAnalisis::asignarNuevoId()
{
}

void ResultadoAnalisis::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json * json_almacenable = new herramientas::utiles::Json(valor_almacenable);

    this->setJson(json_almacenable);

    bool parseo_correcto = this->parsearJson();
}

std::string ResultadoAnalisis::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultado();
}

// CONSULTAS
