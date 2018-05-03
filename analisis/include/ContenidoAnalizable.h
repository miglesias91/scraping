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
    ContenidoAnalizable(std::vector<std::string> bolsa_de_palabras_depurada, double tamanio);
    virtual ~ContenidoAnalizable();

    // GETTERS

    virtual std::vector<std::string> getBolsaDePalabras();

    virtual double getTamanio();

    // SETTERS

    // METODOS

    // CONSULTAS

private:

    std::vector<std::string> bolsa_de_palabras_depurada;
    double tamanio;
};

};
};


