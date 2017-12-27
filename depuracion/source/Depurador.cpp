#include <depuracion/include/Depurador.h>

// stl
#include <algorithm>

// utiles
#include <utiles/include/FuncionesString.h>

using namespace scraping::depuracion;

Depurador::Depurador() : mapa_utf8(NULL)
{
}

Depurador::~Depurador()
{
    if (NULL != this->mapa_utf8)
    {
        delete this->mapa_utf8;
        this->mapa_utf8 = NULL;
    }
}

bool Depurador::cargarMapeoUTF8(std::string path_archivo_mapeo)
{
    if (NULL != this->mapa_utf8)
    {
        delete this->mapa_utf8;
    }


    try
    {
        this->mapa_utf8 = new mapeo::MapaUTF8(path_archivo_mapeo);
    }
    catch (...)
    {
        this->mapa_utf8 = NULL;
        return false;
    }

    return true;
}

ContenidoDepurado Depurador::depurar(IDepurable * depurable)
{
    std::string texto_a_depurar = depurable->getTextoDepurable();

    // 1ero: reemplazo los caracteres especiales: vocales con tildes, letras extrañas, 
    this->reemplazarTodosLosCaracteresEspeciales(texto_a_depurar);

    // 2do: reemplazo las mayusculas por minusculas.
    this->todoMinuscula(texto_a_depurar);

    // 3ero: elimino los simbolos que no forman palabras.
    this->eliminarSignosYPuntuacion(texto_a_depurar);

    // 4to: paso de un texto con palabras a un vector con tokens.
    std::vector<std::string> bolsa_de_palabras = this->tokenizarTexto(texto_a_depurar);

    // 5to: elimino las palabras con menos de 2 letras.
    this->eliminarPalabrasMuyCortas(bolsa_de_palabras);

    // 7to: elimino las palabras con mas de 15 letras.
    this->eliminarPalabrasMuyLargas(bolsa_de_palabras);

    // 8to: elimino las preposiciones.
    this->eliminarPreposiciones(bolsa_de_palabras);

    ContenidoDepurado contenido_depurado(bolsa_de_palabras);
    return contenido_depurado;
}

unsigned int Depurador::eliminarTildes(std::string & texto_a_depurar)
{
    std::vector<std::string> vocales_con_tilde = { u8"á", u8"é", u8"í", u8"ó", u8"ú" };

    unsigned int cantidad_de_tildes_reemplazadas = 0;
    for (std::vector<std::string>::iterator it_vocal = vocales_con_tilde.begin(); it_vocal != vocales_con_tilde.end(); it_vocal++)
    {
        cantidad_de_tildes_reemplazadas += herramientas::utiles::FuncionesString::reemplazarOcurrencias(texto_a_depurar, (*it_vocal), this->mapa_utf8->getTraduccion(*it_vocal));
    }

    return cantidad_de_tildes_reemplazadas;
}

bool Depurador::todoMinuscula(std::string & texto_a_depurar)
{
    return herramientas::utiles::FuncionesString::todoMinuscula(texto_a_depurar);
}

unsigned int Depurador::eliminarSignosYPuntuacion(std::string & texto_a_depurar)
{
    return herramientas::utiles::FuncionesString::eliminarSignosYPuntuacion(texto_a_depurar);
}

std::vector<std::string> Depurador::tokenizarTexto(std::string texto_a_tokenizar)
{
    return herramientas::utiles::FuncionesString::separar(texto_a_tokenizar);
}

unsigned int Depurador::eliminarPreposiciones(std::vector<std::string> & bolsa_de_palabras)
{
    std::vector<std::string> preposiciones = { "a", "ante", "bajo", "cabe", "con", "contra", "cuando", "de", "desde", "donde", "durante", "en", "entre", "excepto", "hacia", "hasta", "mediante", "menos", "para", "por", "segun", "salvo", "sin", "so", "sobre", "tras", "versus", "via" };

    unsigned int cantidad_de_preposiciones_eliminadas = 0;
    for (std::vector<std::string>::iterator it_preposicion = preposiciones.begin(); it_preposicion != preposiciones.end(); it_preposicion++)
    {
        for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
        {
            if (0 == it_preposicion->compare(*it_palabra))
            {
                it_palabra = bolsa_de_palabras.erase(it_palabra);
                cantidad_de_preposiciones_eliminadas++;
            }
            else
            {
                it_palabra++;
            }
        }
    }

    return cantidad_de_preposiciones_eliminadas;
}

unsigned int Depurador::eliminarPalabrasMuyCortas(std::vector<std::string> & bolsa_de_palabras)
{
    unsigned int cantidad_de_palabras_cortas_eliminadas = 0;
    for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
    {
        if (3 > it_palabra->size())
        {
            it_palabra = bolsa_de_palabras.erase(it_palabra);
            cantidad_de_palabras_cortas_eliminadas++;
        }
        else
        {
            it_palabra++;
        }
    }

    return cantidad_de_palabras_cortas_eliminadas;
}

unsigned int Depurador::eliminarPalabrasMuyLargas(std::vector<std::string> & bolsa_de_palabras)
{
    unsigned int cantidad_de_palabras_largas_eliminadas = 0;
    for (std::vector<std::string>::iterator it_palabra = bolsa_de_palabras.begin(); it_palabra != bolsa_de_palabras.end(); )
    {
        if (15 < it_palabra->size())
        {
            it_palabra = bolsa_de_palabras.erase(it_palabra);
            cantidad_de_palabras_largas_eliminadas++;
        }
        else
        {
            it_palabra++;
        }
    }

    return cantidad_de_palabras_largas_eliminadas;
}

unsigned int Depurador::reemplazarTodosLosCaracteresEspeciales(std::string & texto_a_depurar)
{
    unsigned int cantidad_de_reemplazos = 0;
    for (std::string::iterator it = texto_a_depurar.begin(); it != texto_a_depurar.end(); it++)
    {
        unsigned char caracter_1 = *it;
        if (194 <= caracter_1)
        {
            unsigned char caracter_2 = *(it + 1);

            unsigned int valor_decimal_codeunit = (caracter_1 - 192) * 64 + caracter_2 - 128;

            std::string reemplazo = this->mapa_utf8->getTraduccion(valor_decimal_codeunit);

            texto_a_depurar.erase(it, it + 2);
            texto_a_depurar.insert(it, reemplazo.begin(), reemplazo.end());

            cantidad_de_reemplazos++;
        }
    }

    return cantidad_de_reemplazos;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS