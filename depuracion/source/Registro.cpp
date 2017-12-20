#include <depuracion/include/Registro.h>

using namespace scraping::depuracion::mapeo;

Registro::Registro(unsigned int valor_hexa, unsigned char * valor_utf8, std::string descripcion, std::string traduccion) :
    valor_hexa(valor_hexa), descripcion(descripcion), traduccion(traduccion)
{
    memcpy_s(this->valor_utf8, 2, valor_utf8, 2);
}

Registro::~Registro()
{
}

unsigned int Registro::getValorHexa()
{
    return this->valor_hexa;
}

unsigned char * Registro::getValorUTF8()
{
    return this->valor_utf8;
}

std::string Registro::getDescripcion()
{
    return this->descripcion;
}

std::string Registro::getTraduccion()
{
    return this->traduccion;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS