#pragma once

// analisis
#include <analisis/include/ResultadoAnalisis.h>

// preparacion

namespace scraping
{
namespace preparacion
{

class Preparador
{
public:
    Preparador();
    virtual ~Preparador();

    // GETTERS

    // SETTERS

    // METODOS

    virtual bool combinar(std::vector<scraping::analisis::ResultadoAnalisis*> resultados_a_combinar, scraping::analisis::ResultadoAnalisis * resultado_combinacion);

    // CONSULTAS
};

};
};


