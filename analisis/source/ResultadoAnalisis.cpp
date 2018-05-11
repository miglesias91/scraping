#include <analisis/include/ResultadoAnalisis.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::analisis;

ResultadoAnalisis::ResultadoAnalisis(std::string grupo, tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia, tecnicas::ResultadoSentimiento * resultado_sentimiento) : IAlmacenable(grupo), IContieneJson(), resultado_fuerza_en_noticia(resultado_fuerza_en_noticia), resultado_sentimiento(resultado_sentimiento)
{
}

ResultadoAnalisis::~ResultadoAnalisis()
{
    if (nullptr != this->resultado_fuerza_en_noticia)
    {
        delete this->resultado_fuerza_en_noticia;
        this->resultado_fuerza_en_noticia = nullptr;
    }

    if (nullptr != this->resultado_sentimiento)
    {
        delete this->resultado_sentimiento;
        this->resultado_sentimiento = nullptr;
    }
}

// GETTERS

tecnicas::ResultadoFuerzaEnNoticia * ResultadoAnalisis::getResultadoFuerzaEnNoticia()
{
    return this->resultado_fuerza_en_noticia;
}

tecnicas::ResultadoSentimiento * ResultadoAnalisis::getResultadoSentimiento()
{
    return this->resultado_sentimiento;
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

void ResultadoAnalisis::setResultadoSentimiento(tecnicas::ResultadoSentimiento * resultado_sentimiento)
{
    this->resultado_sentimiento = resultado_sentimiento;
}

// METODOS

void ResultadoAnalisis::filtrar(const std::vector<std::string> & terminos_a_filtrar)
{
    this->resultado_fuerza_en_noticia->filtrar(terminos_a_filtrar);
    this->resultado_sentimiento->filtrar(terminos_a_filtrar);
}

void ResultadoAnalisis::combinarCon(ResultadoAnalisis * resultado_a_combinar)
{
    if(nullptr != this->resultado_fuerza_en_noticia && nullptr != resultado_a_combinar->getResultadoFuerzaEnNoticia())
    {
        this->resultado_fuerza_en_noticia->sumarFuerzas(resultado_a_combinar->getResultadoFuerzaEnNoticia());
    }

    if( nullptr != this->resultado_sentimiento && nullptr != resultado_a_combinar->getResultadoSentimiento())
    {
        this->resultado_sentimiento->sumar(resultado_a_combinar->getResultadoSentimiento());
    }
}

// metodos de IContieneJson

bool ResultadoAnalisis::armarJson()
{
    this->getJson()->reset();

    if(nullptr != this->resultado_fuerza_en_noticia)
    {
        this->resultado_fuerza_en_noticia->armarJson();
        this->getJson()->agregarAtributoJson("fuerza_en_noticia", this->resultado_fuerza_en_noticia->getJson());
    }

    if (nullptr != this->resultado_sentimiento)
    {
        this->resultado_sentimiento->armarJson();
        this->getJson()->agregarAtributoJson("sentimiento", this->resultado_sentimiento->getJson());
    }

    return true;
}

bool ResultadoAnalisis::parsearJson()
{
    herramientas::utiles::Json * json_fuerza_en_noticia = nullptr;
    if(this->getJson()->contieneAtributo("fuerza_en_noticia"))
    {
        json_fuerza_en_noticia = this->getJson()->getAtributoValorJson("fuerza_en_noticia");
        this->resultado_fuerza_en_noticia->setJson(json_fuerza_en_noticia);
        this->resultado_fuerza_en_noticia->parsearJson();
    }

    herramientas::utiles::Json * json_sentimiento = nullptr;
    if (this->getJson()->contieneAtributo("sentimiento"))
    {
        json_sentimiento = this->getJson()->getAtributoValorJson("sentimiento");
        this->resultado_sentimiento->setJson(json_sentimiento);
        this->resultado_sentimiento->parsearJson();
    }

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
