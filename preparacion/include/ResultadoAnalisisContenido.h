#pragma once

// analisis
#include <analisis/include/ResultadoAnalisis.h>
#include <analisis/include/ResultadoSentimiento.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoSentimiento.h>


namespace scraping
{
namespace preparacion
{

class ResultadoAnalisisContenido : public scraping::analisis::ResultadoAnalisis
{
public:

    ResultadoAnalisisContenido(
        scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia(),
        scraping::analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento = new scraping::analisis::tecnicas::ResultadoSentimiento()
    );

    virtual ~ResultadoAnalisisContenido();

    // GETTERS

    // SETTERS

    // METODOS

    // metodos de IAlmacenable

    virtual std::string prefijoGrupo();
    
    // CONSULTAS

private:

};

};
};


