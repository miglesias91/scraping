#pragma once

// analisis
#include <analisis/include/IAnalizable.h>
#include <analisis/include/ResultadoAnalisis.h>

namespace scraping
{
namespace analisis
{

class Analizador
{
public:
    Analizador();
    virtual ~Analizador();

    // GETTERS

    // SETTERS

    // METODOS

    virtual ResultadoAnalisis analizar(IAnalizable * contenido_a_analizar);

    // CONSULTAS
};

};
};


