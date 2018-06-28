#include <depuracion/include/ContenidoDepurado.h>

// utiles
#include <utiles/include/FuncionesString.h>

namespace scraping::depuracion {

ContenidoDepurado::ContenidoDepurado() : IAlmacenable(scraping::ConfiguracionScraping::prefijoContenidoDepurado()) {}

ContenidoDepurado::ContenidoDepurado(std::vector<std::string> bolsa_de_palabras_depurada) : bolsa_de_palabras_depurada(bolsa_de_palabras_depurada) {}

ContenidoDepurado::~ContenidoDepurado() {}

std::vector<std::string> ContenidoDepurado::getBolsaDePalabras() {

    return this->bolsa_de_palabras_depurada;
}

void ContenidoDepurado::bolsa_de_palabras(const std::vector<std::string>& bolsa_de_palabras_depurada) {
    this->bolsa_de_palabras_depurada = bolsa_de_palabras_depurada;
}

std::string ContenidoDepurado::getValorAlmacenable() {
    return herramientas::utiles::FuncionesString::unir(this->bolsa_de_palabras_depurada, " ");
}

void ContenidoDepurado::asignarNuevoId() {
}

void ContenidoDepurado::parsearValorAlmacenable(std::string valor_almacenable) {
    this->bolsa_de_palabras_depurada = herramientas::utiles::FuncionesString::separar(valor_almacenable, " ");
}

std::string ContenidoDepurado::prefijoGrupo() {
    return scraping::ConfiguracionScraping::prefijoContenidoDepurado();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS

bool ContenidoDepurado::vacio() {
    return this->bolsa_de_palabras_depurada.empty();
}

};