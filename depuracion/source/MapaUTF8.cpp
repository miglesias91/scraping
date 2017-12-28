#include <depuracion/include/MapaUTF8.h>

// stl
#include <iostream>
#include <fstream>

// utiles
#include <utiles/include/FuncionesString.h>

using namespace scraping::depuracion::mapeo;

MapaUTF8::MapaUTF8(std::string path_archivo_mapa)
{
    std::ifstream archivo_mapeo(path_archivo_mapa);

    std::string linea_mapeo;

    unsigned int hexa = 0;
    unsigned char * utf8_codeunits_en_decimal;
    std::string descripcion = "";
    std::string valor_traducido = "";

    try {
        while (false == archivo_mapeo.eof())
        {
            std::getline(archivo_mapeo, linea_mapeo);
            std::vector<std::string> campos = herramientas::utiles::FuncionesString::separar(linea_mapeo, ",");

            // parseo los campos
            hexa = std::stoul(campos[0], NULL, 16);

            std::vector<std::string> valores_utf8 = herramientas::utiles::FuncionesString::separar(campos[2]);

            unsigned int cantidad_de_codeunits = valores_utf8.size();
            utf8_codeunits_en_decimal = new unsigned char[cantidad_de_codeunits];

            unsigned int i = 0;
            for (std::vector<std::string>::iterator it = valores_utf8.begin(); it != valores_utf8.end(); it++)
            {
                utf8_codeunits_en_decimal[i] = std::stoul(*it);
                i++;
            }

            descripcion = campos[3];

            valor_traducido = campos[4];

            Registro * nuevo_registro = new Registro(hexa, utf8_codeunits_en_decimal, cantidad_de_codeunits, descripcion, valor_traducido);

            this->mapa_valores_hexa.insert(std::pair<unsigned int, Registro*>(hexa, nuevo_registro));
            this->mapa_valores_decimales_ncr.insert(std::pair<std::string, Registro*>(campos[1], nuevo_registro));

            delete[] utf8_codeunits_en_decimal;
        }
    }
    catch (...)
    {
        throw std::exception("Error al cargar el archivo de mapeo UTF8.");
    }
}

MapaUTF8::~MapaUTF8()
{
    // solo elimino un mapa xq los dos tienen los mismo registros.
    for (std::unordered_map<unsigned int, Registro*>::iterator it = this->mapa_valores_hexa.begin(); it != this->mapa_valores_hexa.end(); it++)
    {
        delete it->second;
        it->second = NULL;
    }
}

std::string MapaUTF8::getTraduccion(unsigned int valor_hexa)
{
    return this->mapa_valores_hexa[valor_hexa]->getTraduccion();
}

std::string MapaUTF8::getTraduccion(std::string caracter_especial)
{
    return this->mapa_valores_decimales_ncr[caracter_especial]->getTraduccion();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS