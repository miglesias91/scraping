#pragma once

// stl
#include <string>
#include <unordered_map>

// depuracion
#include <depuracion/include/Registro.h>

namespace scraping
{
namespace depuracion
{
namespace mapeo
{

class MapaUTF8
{
public:
    MapaUTF8(std::string path_archivo_mapa = "");
    virtual ~MapaUTF8();

    // GETTERS

    // 'valor_hexa' representa al valor en hexadecimal del caracter especial.
    std::string getTraduccion(unsigned int valor_hexa);
    
    // 'caracter especial' representa al conjunto de valores 'char' que representan al caracter especial en UTF8.
    // ejemplo:
    //  caracter especial = 'é'
    //  representacion en valores 'char' = 'Ã©'
    std::string getTraduccion(std::string caracter_especial_en_utf8);

    // SETTERS

    // METODOS

    // CONSULTAS

private:

    // ATRIBUTOS

    std::unordered_map<unsigned int, Registro*> mapa_valores_hexa;
    std::unordered_map<std::string, Registro*> mapa_valores_decimales_ncr;
};

};
};
};


