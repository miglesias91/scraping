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
    void sentimiento_de_categoria(scraping::analisis::tecnicas::ResultadoSentimiento* resultado, const std::string & categoria) const;
    void fuerza_en_noticia_de_categoria(scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia* resultado, const std::string & categoria) const;
    void resultado_de_categoria(ResultadoAnalisisContenido* resultado, const std::string & categoria) const;
    void resultados_por_categoria(std::unordered_map<std::string, ResultadoAnalisisContenido*> * resultados);

    // SETTERS

    void set_resultado_de_categoria(const std::string & categoria, ResultadoAnalisisContenido * resultado);

    // METODOS

    // metodos de ResultadoAnalisis
    virtual void combinarCon(ResultadoAnalisisMedio * resultado_a_combinar);

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


