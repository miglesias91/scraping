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

// metodos de IContieneJson

bool Cuenta::armarJson()
{
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("nombre_cuenta", this->getNombre());

    return true;
}

bool Cuenta::parsearJson()
{
    std::string nombre_cuenta = this->getJson()->getAtributoValorString("nombre_cuenta");

    this->setNombre(nombre_cuenta);

    return true;
}

// CONSULTAS