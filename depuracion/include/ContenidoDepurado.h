#pragma once

// stl
#include <string>
#include <vector>

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

private:

    std::vector<std::string> bolsa_de_palabras_depurada;
};

};
};


