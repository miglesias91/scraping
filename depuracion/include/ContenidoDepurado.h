#pragma once

// stl
#include <string>

namespace scraping
{
namespace depuracion
{

class ContenidoDepurado
{
public:
    ContenidoDepurado(std::string texto_depurado = "");
    virtual ~ContenidoDepurado();

    // GETTERS

    // SETTERS

    // METODOS

    // CONSULTAS

private:

    std::string texto_depurado;
};

};
};


