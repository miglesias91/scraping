#include <depuracion/include/ContenidoDepurado.h>

using namespace scraping::depuracion;

ContenidoDepurado::ContenidoDepurado(std::vector<std::string> bolsa_de_palabras_depurada) : bolsa_de_palabras_depurada(bolsa_de_palabras_depurada)
{
}

ContenidoDepurado::~ContenidoDepurado()
{
}

std::vector<std::string> ContenidoDepurado::getBolsaDePalabras()
{
    return this->bolsa_de_palabras_depurada;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS