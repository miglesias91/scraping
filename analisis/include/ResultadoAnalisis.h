#pragma once

// analisis
#include <analisis/include/ResultadoFuerzaEnNoticia.h>

// herramientas
#include <utiles/include/IContieneJson.h>

namespace scraping
{
namespace analisis
{

class ResultadoAnalisis : public herramientas::utiles::IContieneJson, public scraping::IAlmacenable
{
public:

    ResultadoAnalisis(tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new tecnicas::ResultadoFuerzaEnNoticia());

    virtual ~ResultadoAnalisis();

    // GETTERS

    tecnicas::ResultadoFuerzaEnNoticia * getResultadoFuerzaEnNoticia();

    // SETTERS

    // METODOS


    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia;
};

};
};


