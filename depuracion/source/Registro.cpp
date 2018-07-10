#include <depuracion/include/Registro.h>

using namespace scraping::depuracion::mapeo;

Registro::Registro(unsigned int valor_hexa, unsigned char * utf8_codeunits_en_decimal, unsigned int cantidad_de_codeunits, std::string descripcion, std::string traduccion) :
    valor_hexa(valor_hexa), utf8_codeunits_en_decimal(nullptr), cantidad_de_codeunits(cantidad_de_codeunits), descripcion(descripcion), traduccion(traduccion)
{
    this->utf8_codeunits_en_decimal = new unsigned char[cantidad_de_codeunits];

    memcpy_s(this->utf8_codeunits_en_decimal, cantidad_de_codeunits, utf8_codeunits_en_decimal, cantidad_de_codeunits);
}

Registro::~Registro()
{
    delete[] this->utf8_codeunits_en_decimal;
}

unsigned int Registro::getValorHexa()
{
    return this->valor_hexa;
}

unsigned char * Registro::getCodeunitsUTF8EnDecimal()
{
    return this->utf8_codeunits_en_decimal;
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