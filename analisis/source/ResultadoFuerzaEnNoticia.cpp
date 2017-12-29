#include <analisis/include/ResultadoFuerzaEnNoticia.h>

using namespace scraping::analisis::tecnicas;

ResultadoFuerzaEnNoticia::ResultadoFuerzaEnNoticia() : IResultadoTecnica()
{
}

ResultadoFuerzaEnNoticia::~ResultadoFuerzaEnNoticia()
{
}

// GETTERS

// SETTERS

// METODOS

bool ResultadoFuerzaEnNoticia::agregarResultado(std::string palabra, float fuerza_en_noticia)
{
    if (this->fuerza_por_palabra.end() != this->fuerza_por_palabra.find(palabra))
    {
        return false;
    }

    this->fuerza_por_palabra[palabra] = fuerza_en_noticia;
    return true;
}

// CONSULTAS
