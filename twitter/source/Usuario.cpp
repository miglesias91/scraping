#include <twitter/include/Usuario.h>

using namespace scraping::twitter::modelo;

Usuario::Usuario(std::string nombre) : nombre(nombre)
{
}

Usuario::~Usuario()
{
}

// GETTERS

std::string Usuario::getNombre()
{
    return this->nombre;
}

// SETTERS

void Usuario::setNombre(std::string nombre)
{
    this->nombre = nombre;
}

// METODOS

// CONSULTAS