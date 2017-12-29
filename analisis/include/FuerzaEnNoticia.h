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
    FuerzaEnNoticia();
    virtual ~FuerzaEnNoticia();

    // GETTERS

    // SETTERS

    // METODOS

    // metodos ITecnica

    // recibe una bolsa de palabras y devuelve un vector con la fuerza de cada palabra en la bolsa de palabras.
    virtual ResultadoFuerzaEnNoticia aplicar(std::vector<std::string> bolsa_de_palabras);

    // CONSULTAS
};

};
};
};