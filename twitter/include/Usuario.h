#pragma once

// stl
#include <string>

namespace scraping
{
namespace twitter
{
namespace modelo
{

class Usuario
{
public:
    Usuario(std::string nombre = "");
    virtual ~Usuario();

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


