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

    // 3ero: elimino los signos de puntuacion.
    this->eliminarSignosDePuntuacion(texto_a_depurar);

    ContenidoDepurado texto_depurado(texto_a_depurar);
    return texto_depurado;
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
    std::transform(texto_a_depurar.begin(), texto_a_depurar.end(), texto_a_depurar.begin(), ::tolower);
    return true;
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

unsigned int Depurador::eliminarSimbolosNoCaracteres(std::string & texto_a_depurar)
{
    std::vector<std::string> vocales_con_tilde = { "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "[", "\\", "]", "^", "_", "`", "{", "|", "}", "~" };

    for (std::vector<std::string>::iterator it_vocal = vocales_con_tilde.begin(); it_vocal != vocales_con_tilde.end(); it_vocal++)
    {
        herramientas::utiles::FuncionesString::eliminarOcurrencias(texto_a_depurar, (*it_vocal), this->mapa_utf8->getTraduccion(*it_vocal));
    }

    return true;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS