#pragma once

// herramientas
#include <utiles/include/IContieneJson.h>

// scraping
#include <scraping/include/IAlmacenable.h>

// analisis
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoSentimiento.h>

namespace scraping
{
namespace analisis
{

class ResultadoAnalisis : public scraping::IAlmacenable, public herramientas::utiles::IContieneJson
{
public:

    ResultadoAnalisis(std::string grupo, tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = nullptr, tecnicas::ResultadoSentimiento * resultado_sentimiento = nullptr);

    virtual ~ResultadoAnalisis();

    // GETTERS

    tecnicas::ResultadoFuerzaEnNoticia * getResultadoFuerzaEnNoticia();

    tecnicas::ResultadoSentimiento * getResultadoSentimiento();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    void setResultadoFuerzaEnNoticia(tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia);

    void setResultadoSentimiento(tecnicas::ResultadoSentimiento * resultado_sentimiento);

    // METODOS

    virtual void combinarCon(ResultadoAnalisis * resultado_a_combinar);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    // CONSULTAS

private:

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia;

    tecnicas::ResultadoSentimiento * resultado_sentimiento;

};

};
};


