#pragma once

// analisis
#include <analisis/include/ResultadoAnalisis.h>
#include <analisis/include/ResultadoSentimiento.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoSentimiento.h>

// preparacion
#include <preparacion/include/ResultadoAnalisisContenido.h>

namespace scraping
{
namespace preparacion
{

class ResultadoAnalisisMedio : public scraping::analisis::ResultadoAnalisis
{
public:

    ResultadoAnalisisMedio(
        scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia(),
        scraping::analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento = new scraping::analisis::tecnicas::ResultadoSentimiento()
    );

    virtual ~ResultadoAnalisisMedio();

    // GETTERS

    // SETTERS

    void resultado_de_categoria(const std::string & categoria, ResultadoAnalisisContenido * resultado);

    // METODOS

    // metodos de IAlmacenable

    virtual std::string prefijoGrupo();
    
    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:
    std::unordered_map<std::string, ResultadoAnalisisContenido*> resultados;  // map<categoria, resultados>
};

};
};


