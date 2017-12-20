#include <depuracion/include/Depurador.h>

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

    this->eliminarTildes(texto_a_depurar);
    this->todoMinuscula(texto_a_depurar);
    this->reemplazarCaracteresEspeciales(texto_a_depurar);

    ContenidoDepurado texto_depurado(texto_a_depurar);
    return texto_depurado;
}

bool Depurador::eliminarTildes(std::string & texto_a_depurar)
{
    std::vector<std::string> vocales_con_tilde = { u8"á", u8"é", u8"í", u8"ó", u8"ú" };

    for (std::vector<std::string>::iterator it_vocal = vocales_con_tilde.begin(); it_vocal != vocales_con_tilde.end(); it_vocal++)
    {
        herramientas::utiles::FuncionesString::reemplazarOcurrencias(texto_a_depurar, (*it_vocal), this->mapa_utf8->getTraduccion(*it_vocal));
    }

    return true;
}

bool Depurador::todoMinuscula(std::string & texto_a_depurar)
{
    return false;
}

bool Depurador::reemplazarCaracteresEspeciales(std::string & texto_a_depurar)
{
    return false;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS