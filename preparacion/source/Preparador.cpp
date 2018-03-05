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
    unsigned int cantidad_de_fuerzas_sumadas = 0;
    for (std::vector<analisis::ResultadoAnalisis*>::iterator it = resultados_a_combinar.begin(); it != resultados_a_combinar.end(); it++)
    {
        cantidad_de_fuerzas_sumadas += resultado_combinacion->combinarCon(*it);
    }

    return cantidad_de_fuerzas_sumadas;
}

// CONSULTAS