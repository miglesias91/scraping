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

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int reemplazarTodosLosCaracteresEspeciales(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int eliminarTildes(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8, y NO DEBE TENER CARACTERES ESPECIALES (es decir, primero hay que aplicarle el metodo 'reemplazarTodosLosCaracteresEspeciales').
    virtual bool todoMinuscula(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int eliminarSimbolosNoCaracteres(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8, y NO DEBE TENER CARACTERES ESPECIALES (es decir, primero hay que aplicarle el metodo 'reemplazarTodosLosCaracteresEspeciales').
    virtual unsigned int eliminarSignosDePuntuacion(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8, y NO DEBE TENER CARACTERES ESPECIALES (es decir, primero hay que aplicarle el metodo 'reemplazarTodosLosCaracteresEspeciales').
    virtual std::vector<std::string> tokenizarTexto(std::string texto_a_tokenizar);

    // eliminas las preposiciones de la bolas de palabras.
    virtual unsigned int eliminarPreposiciones(std::vector<std::string> & bolsa_de_palabras);

    // eliminas las palabras muy cortas de la bolsa de palabtas (palabra muy corta tiene 1 o 2 letras).
    virtual unsigned int eliminarPalabrasMuyCortas(std::vector<std::string> & bolsa_de_palabras);

    // eliminas las palabras muy largas de la bolsa de palabtas (palabra muy larga tiene mas de 15 letras).
    virtual unsigned int eliminarPalabrasMuyLargas(std::vector<std::string> & bolsa_de_palabras);

    // CONSULTAS


private:

    // mapa que contiene la traduccion de cada caracter especial a su valor de caracter normal.
    mapeo::MapaUTF8 * mapa_utf8;

};

};
};


