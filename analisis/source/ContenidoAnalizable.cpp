#include <analisis/include/ContenidoAnalizable.h>

using namespace scraping::analisis;

ContenidoAnalizable::ContenidoAnalizable(std::vector<std::string> bolsa_de_palabras_depurada) : IAnalizable(), bolsa_de_palabras_depurada(bolsa_de_palabras_depurada)
{
}

ContenidoAnalizable::~ContenidoAnalizable()
{
}

std::vector<std::string> ContenidoAnalizable::getBolsaDePalabras()
{
    return this->bolsa_de_palabras_depurada;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS