#pragma once

// stl
#include <unordered_map>
#include <mutex>
#include <thread>

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

    static void setMapaUTF8(mapeo::MapaUTF8 * mapa_utf8);

    static void setStopwords(std::vector<std::string> stopwords);

    // METODOS

    virtual bool depurar_twitter();
    virtual bool depurar_facebook();
    virtual bool depurar_portales();

    virtual bool depurar(scraping::extraccion::Medio * medio);

    virtual bool cargarMapeoUTF8(std::string path_archivo_mapeo);

    virtual bool depurar(IDepurable * depurable, ContenidoDepurado * depurado);

    virtual ContenidoDepurado depurarConTildes(IDepurable * depurable);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int reemplazarTodosLosCaracteresEspeciales(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int reemplazarTodosLosCaracteresEspecialesExceptoTildes(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int eliminarTildes(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8, y NO DEBE TENER CARACTERES ESPECIALES (es decir, primero hay que aplicarle el metodo 'reemplazarTodosLosCaracteresEspeciales').
    virtual bool todoMinuscula(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int eliminarSignosYPuntuacion(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int eliminarCaracteresDeControl(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8.
    virtual unsigned int eliminarURLs(std::string & texto_a_depurar);

    // 'texto_a_depurar' tiene que estar formateado como UTF8, y NO DEBE TENER CARACTERES ESPECIALES (es decir, primero hay que aplicarle el metodo 'reemplazarTodosLosCaracteresEspeciales').
    virtual std::vector<std::string> tokenizarTexto(std::string texto_a_tokenizar);

    // eliminas las palabras muy cortas de la bolsa de palabtas (palabra muy corta tiene 1 o 2 letras).
    virtual unsigned int eliminarPalabrasMuyCortas(std::vector<std::string> & bolsa_de_palabras);

    // eliminas las palabras muy largas de la bolsa de palabtas (palabra muy larga tiene mas de 15 letras).
    virtual unsigned int eliminarPalabrasMuyLargas(std::vector<std::string> & bolsa_de_palabras);

    // eliminas las preposiciones de la bolsa de palabras.
    virtual unsigned int eliminarPreposiciones(std::vector<std::string> & bolsa_de_palabras);

    // eliminas los pronombres de la bolsa de palabras.
    virtual unsigned int eliminarPronombres(std::vector<std::string> & bolsa_de_palabras);

    // eliminas las stopwords de la bolsa de palabras.
    virtual unsigned int eliminarStopwords(std::vector<std::string> & bolsa_de_palabras);

    static bool cargarStopwords(std::string path_archivo_stopwords);

    // CONSULTAS


private:

    // METODOS PRIVADOS

    // ATRIBUTOS

    // mapa que contiene la traduccion de cada caracter especial a su valor de caracter normal.
    static mapeo::MapaUTF8 * mapa_utf8;

    static std::vector<std::string> stopwords_espaniol;

    std::mutex mutex;
};

};
};


