#pragma once

// stl
#include <string>

namespace scraping
{
namespace depuracion
{
namespace mapeo
{

class Registro
{
public:
    Registro(unsigned int valor_hexa, unsigned char * utf8_codeunits_en_decimal, unsigned int cantidad_de_codeunits, std::string descripcion, std::string traduccion);
    virtual ~Registro();

    // GETTERS

    unsigned int getValorHexa();

    unsigned char * getCodeunitsUTF8EnDecimal();

    std::string getDescripcion();

    std::string getTraduccion();

    // SETTERS

    // METODOS

    // CONSULTAS

private:

    // ATRIBUTOS

    unsigned int valor_hexa;

    unsigned char * utf8_codeunits_en_decimal;

    unsigned int cantidad_de_codeunits;

    std::string descripcion;

    std::string traduccion;
};

};
};
};


