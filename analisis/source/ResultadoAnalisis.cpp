#include <analisis/include/ResultadoAnalisis.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::analisis;

ResultadoAnalisis::ResultadoAnalisis(std::string grupo, tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia) : IAlmacenable(grupo), IContieneJson(), resultado_fuerza_en_noticia(resultado_fuerza_en_noticia)
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

// SETTERS

void ResultadoAnalisis::setResultadoFuerzaEnNoticia(tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia)
{
    this->resultado_fuerza_en_noticia = resultado_fuerza_en_noticia;
}

// METODOS

unsigned int ResultadoAnalisis::combinarCon(ResultadoAnalisis * resultado_a_combinar)
{
    return this->resultado_fuerza_en_noticia->sumarFuerzas(resultado_a_combinar->getResultadoFuerzaEnNoticia());
}

// metodos de IContieneJson

bool ResultadoAnalisis::armarJson()
{
    this->getJson()->reset();

    this->resultado_fuerza_en_noticia->armarJson();

    this->getJson()->agregarAtributoJson("fuerza_en_noticia", this->resultado_fuerza_en_noticia->getJson());

    return true;
}

bool ResultadoAnalisis::parsearJson()
{
    herramientas::utiles::Json * json_fuerza_en_noticia = this->getJson()->getAtributoValorJson("fuerza_en_noticia");

    this->resultado_fuerza_en_noticia->setJson(json_fuerza_en_noticia);
    this->resultado_fuerza_en_noticia->parsearJson();

    return true;
}

// metodos de IAlmacenable

void ResultadoAnalisis::asignarNuevoId()
{
}

void ResultadoAnalisis::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json * json_almacenable = new herramientas::utiles::Json(valor_almacenable);

    this->setJson(json_almacenable);

    bool parseo_correcto = this->parsearJson();
}

// CONSULTAS
