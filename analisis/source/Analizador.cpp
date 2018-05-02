#include <analisis/include/Analizador.h>

// analisis
#include <analisis/include/CantidadDeApariciones.h>
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/Sentimiento.h>

// preparacion
#include <preparacion/include/ResultadoAnalisisContenido.h>

using namespace scraping::analisis;

Analizador::Analizador(std::vector<tecnicas::ITecnica*> tecnicas_a_aplicar) : tecnicas_a_aplicar(tecnicas_a_aplicar)
{
}

Analizador::~Analizador()
{
}

ResultadoAnalisis * Analizador::analizar(IAnalizable * contenido_a_analizar)
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_a_analizar = contenido_a_analizar->getBolsaDePalabras();

    tecnicas::ResultadoFuerzaEnNoticia resultado_fuerza_en_noticia;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_a_analizar, resultado_fuerza_en_noticia);



    return new scraping::preparacion::ResultadoAnalisisContenido();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS

