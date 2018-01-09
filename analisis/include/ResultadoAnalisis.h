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

    ResultadoAnalisis(tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new tecnicas::ResultadoFuerzaEnNoticia());

    virtual ~ResultadoAnalisis();

    // GETTERS

    tecnicas::ResultadoFuerzaEnNoticia * getResultadoFuerzaEnNoticia();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    // METODOS


    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS

private:

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia;
};

};
};


