#pragma once

// herramientas
#include <utiles/include/IContieneJson.h>

// scraping
#include <scraping/include/IAlmacenable.h>

// analisis
#include <analisis/include/ResultadoFuerzaEnNoticia.h>

namespace scraping
{
namespace analisis
{

class ResultadoAnalisis : public scraping::IAlmacenable, public herramientas::utiles::IContieneJson
{
public:

    ResultadoAnalisis(std::string grupo, tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = nullptr);

    virtual ~ResultadoAnalisis();

    // GETTERS

    tecnicas::ResultadoFuerzaEnNoticia * getResultadoFuerzaEnNoticia();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    void setResultadoFuerzaEnNoticia(tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia);

    // METODOS

    virtual unsigned int combinarCon(ResultadoAnalisis * resultado_a_combinar);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    // CONSULTAS

private:

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia;
};

};
};


