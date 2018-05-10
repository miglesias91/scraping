#pragma once

// stl
#include <string>
#include <vector>

// analisis
#include <analisis/include/IAnalizable.h>

namespace scraping
{
namespace depuracion
{

class ContenidoDepurado
{
public:
    ContenidoDepurado(std::vector<std::string> bolsa_de_palabras_depurada);
    virtual ~ContenidoDepurado();

    // GETTERS

    std::vector<std::string> getBolsaDePalabras();

    // SETTERS

    // METODOS

    // CONSULTAS

    bool vacio();

private:

    std::vector<std::string> bolsa_de_palabras_depurada;
};

};
};


