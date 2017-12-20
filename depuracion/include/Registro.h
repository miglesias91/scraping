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
    Registro(unsigned int valor_hexa, unsigned char * valor_utf8, std::string descripcion, std::string traduccion);
    virtual ~Registro();

    // GETTERS

    unsigned int getValorHexa();

    unsigned char * getValorUTF8();

    std::string getDescripcion();

    std::string getTraduccion();

    // SETTERS

    // METODOS

    // CONSULTAS

private:

    // ATRIBUTOS

    unsigned int valor_hexa;

    unsigned char valor_utf8[2];

    std::string descripcion;

    std::string traduccion;
};

};
};
};


