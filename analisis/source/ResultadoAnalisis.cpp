#include <analisis/include/ResultadoAnalisis.h>

using namespace scraping::analisis;

ResultadoAnalisis::ResultadoAnalisis(tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia) : IContieneJson(), resultado_fuerza_en_noticia(resultado_fuerza_en_noticia)
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

tecnicas::ResultadoFuerzaEnNoticia * ResultadoAnalisis::getResultadoFuerzaEnNoticia()
{
    return this->resultado_fuerza_en_noticia;
}

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

// GETTERS

// SETTERS

// METODOS

// CONSULTAS
