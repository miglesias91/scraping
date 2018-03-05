#pragma once

// analisis
#include <analisis/include/ITecnica.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class FuerzaEnNoticia : public ITecnica
{
public:
    FuerzaEnNoticia(float fuerza_minima = 0);
    virtual ~FuerzaEnNoticia();

    // GETTERS

    // SETTERS

    // METODOS

    // metodos ITecnica

    // recibe una bolsa de palabras y devuelve un vector con la fuerza de cada palabra en la bolsa de palabras.
    // El valor de retorno indica el "factor de tamanio de la bolsa (= log10(cantidad de caracteres en bolsa de palabras))".
    virtual double aplicar(std::vector<std::string> bolsa_de_palabras, IResultadoTecnica & resultado);

    // CONSULTAS

private:

    // valor a partir del cual se consideran relevante la fuerza de un termino.
    float fuerza_minima;
};

};
};
};