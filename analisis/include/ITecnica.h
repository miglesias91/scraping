#pragma once

// stl
#include <string>
#include <vector>

// analisis
#include <analisis/include/IResultadoTecnica.h>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class ITecnica
{
public:
    ITecnica();
    virtual ~ITecnica();

    // GETTERS

    // SETTERS

    // METODOS

    virtual IResultadoTecnica * aplicar(std::vector<std::string> bolsa_de_palabras) = 0;

    // CONSULTAS
};

};
};
};