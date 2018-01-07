#pragma once

// stl
#include <string>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping
{
namespace twitter
{
namespace modelo
{

class Cuenta : public scraping::extraccion::Medio
{
public:
    Cuenta(std::string nombre = "");
    virtual ~Cuenta();

    // GETTERS

    std::string getNombre();

    // SETTERS

    void setNombre(std::string nombre);

    // METODOS

    // CONSULTAS

private:

    // ATRIBUTOS

    std::string nombre;
};

};
};
};


