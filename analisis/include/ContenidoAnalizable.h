#pragma once

// stl
#include <string>
#include <vector>

// analisis
#include <analisis/include/IAnalizable.h>

namespace scraping
{
namespace analisis
{

class ContenidoAnalizable : public scraping::analisis::IAnalizable
{
public:
    ContenidoAnalizable(std::vector<std::string> bolsa_de_palabras_depurada);
    virtual ~ContenidoAnalizable();

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


