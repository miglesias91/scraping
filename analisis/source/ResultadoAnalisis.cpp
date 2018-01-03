#include <analisis/include/ResultadoAnalisis.h>

using namespace scraping::analisis;

ResultadoAnalisis::ResultadoAnalisis() : IContieneJson()
{
}

ResultadoAnalisis::ResultadoAnalisis(tecnicas::ResultadoFuerzaEnNoticia resultado_fuerza_en_noticia) : IContieneJson(), resultado_fuerza_en_noticia(resultado_fuerza_en_noticia)
{
}

ResultadoAnalisis::~ResultadoAnalisis()
{
}

bool ResultadoAnalisis::armarJson()
{
    return false;
}

bool ResultadoAnalisis::parsearJson()
{
    return false;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS
