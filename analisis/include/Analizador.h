#pragma once

// analisis
#include <analisis/include/IAnalizable.h>
#include <analisis/include/ResultadoAnalisis.h>
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/Sentimiento.h>

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

    virtual void analizar(IAnalizable * contenido_a_analizar, ResultadoAnalisis * resultado_analisis);

    // CONSULTAS

private:
};

};
};


