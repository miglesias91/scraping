#pragma once

// stl
#include <unordered_map>

// depuracion
#include <depuracion/include/ContenidoDepurado.h>
#include <depuracion/include/IDepurable.h>
#include <depuracion/include/MapaUTF8.h>

namespace scraping
{
namespace depuracion
{

class Depurador
{
public:
    Depurador();
    virtual ~Depurador();
    
    // GETTERS

    // SETTERS

    // METODOS

    virtual bool cargarMapeoUTF8(std::string path_archivo_mapeo);

    virtual ContenidoDepurado depurar(IDepurable * depurable);

    virtual bool eliminarTildes(std::string & texto_a_depurar);

    virtual bool todoMinuscula(std::string & texto_a_depurar);

    virtual bool reemplazarCaracteresEspeciales(std::string & texto_a_depurar);

    // CONSULTAS


private:

    // mapa que contiene la traduccion de cada caracter especial a su valor de caracter normal.
    mapeo::MapaUTF8 * mapa_utf8;

};

};
};


