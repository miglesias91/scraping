#include <analisis/include/Analizador.h>

// analisis
#include <analisis/include/CantidadDeApariciones.h>
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/Sentimiento.h>

// preparacion
#include <preparacion/include/ResultadoAnalisisContenido.h>

using namespace scraping::analisis;

Analizador::Analizador()
{
}

Analizador::~Analizador()
{
}

void Analizador::analizar(IAnalizable * contenido_a_analizar, ResultadoAnalisis * resultado_analisis)
{
    // aplico 'fuerza en noticia'
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;
    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(contenido_a_analizar, resultado_fuerza_en_noticia);
    resultado_analisis->setResultadoFuerzaEnNoticia(resultado_fuerza_en_noticia);

    // aplico 'sentimiento'
    tecnicas::Sentimiento sentimiento;
    tecnicas::ResultadoSentimiento resultado_sentimiento;
    sentimiento.aplicar(contenido_a_analizar, resultado_sentimiento);
    resultado_analisis->setResultadoSentimiento(resultado_fuerza_en_noticia);

    return new scraping::preparacion::ResultadoAnalisisContenido();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS

