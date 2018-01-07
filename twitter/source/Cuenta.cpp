#include <twitter/include/Cuenta.h>

using namespace scraping::twitter::modelo;

Cuenta::Cuenta(std::string nombre) : Medio(), nombre(nombre)
{
}

Cuenta::~Cuenta()
{
}

// GETTERS

std::string Cuenta::getNombre()
{
    return this->nombre;
}

// SETTERS

void Cuenta::setNombre(std::string nombre)
{
    this->nombre = nombre;
}

// METODOS

// CONSULTAS