#pragma once

// utiles
#include <utiles/include/Fecha.h>

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

    herramientas::utiles::Fecha fecha() const;
    std::string categoria() const;

    // SETTERS

    void fecha(const herramientas::utiles::Fecha & fecha_contenido);
    void categoria(const std::string & categoria_contenido);

    // METODOS

    // metodos de IAlmacenable

    virtual std::string prefijoGrupo();
    
    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:
    herramientas::utiles::Fecha fecha_resultado;
    std::string categoria_contenido;
};

};
};


