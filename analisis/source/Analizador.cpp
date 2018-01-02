#include <analisis/include/Analizador.h>

// analisis
#include <analisis/include/CantidadDeApariciones.h>
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/Sentimiento.h>

using namespace scraping::analisis;

Analizador::Analizador()
{
}

Analizador::~Analizador()
{
}

ResultadoAnalisis Analizador::analizar(IAnalizable * contenido_a_analizar)
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_a_analizar = contenido_a_analizar->getBolsaDePalabras();

    tecnicas::ResultadoFuerzaEnNoticia resultado_fuerza_en_noticia;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_a_analizar, resultado_fuerza_en_noticia);



    return ResultadoAnalisis();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS

