#include <analisis/include/ContenidoAnalizable.h>

using namespace scraping::analisis;

ContenidoAnalizable::ContenidoAnalizable(std::vector<std::string> bolsa_de_palabras_depurada, double tamanio)
    : IAnalizable(), bolsa_de_palabras_depurada(bolsa_de_palabras_depurada), tamanio(tamanio)
{
}

ContenidoAnalizable::~ContenidoAnalizable()
{
}

std::vector<std::string> ContenidoAnalizable::getBolsaDePalabras()
{
    return this->bolsa_de_palabras_depurada;
}

double ContenidoAnalizable::getTamanio()
{
    return this->tamanio;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS