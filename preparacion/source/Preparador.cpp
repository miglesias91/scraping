#include <preparacion/include/Preparador.h>

using namespace scraping::preparacion;

Preparador::Preparador()
{
}

Preparador::~Preparador()
{
}

// GETTERS

// SETTERS

// METODOS

bool Preparador::combinar(std::vector<scraping::analisis::ResultadoAnalisis*> resultados_a_combinar, scraping::analisis::ResultadoAnalisis * resultado_combinacion)
{
    for (std::vector<analisis::ResultadoAnalisis*>::iterator it = resultados_a_combinar.begin(); it != resultados_a_combinar.end(); it++)
    {
        resultado_combinacion->combinarCon(*it);
    }

    return true;
}

// CONSULTAS