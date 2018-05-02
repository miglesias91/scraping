#pragma once

// analisis
#include <analisis/include/IAnalizable.h>
#include <analisis/include/ResultadoAnalisis.h>
#include <analisis/include/ITecnica.h>

namespace scraping
{
namespace analisis
{

class Analizador
{
public:
    Analizador(std::vector<tecnicas::ITecnica*> tecnicas_a_aplicar);
    virtual ~Analizador();

    // GETTERS

    // SETTERS

    // METODOS

    virtual ResultadoAnalisis * analizar(IAnalizable * contenido_a_analizar);

    // CONSULTAS

private:

    std::vector<tecnicas::ITecnica*> tecnicas_a_aplicar;
};

};
};


