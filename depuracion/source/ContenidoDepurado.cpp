#include <depuracion/include/ContenidoDepurado.h>

// utiles
#include <utiles/include/FuncionesString.h>
#include <utiles/include/Json.h>

namespace scraping::depuracion {

ContenidoDepurado::ContenidoDepurado() : IAlmacenable(scraping::ConfiguracionScraping::prefijoContenidoDepurado()) {}

ContenidoDepurado::ContenidoDepurado(const std::vector<std::string> & bolsa_de_palabras_depurada, const uint32_t & tamanio)
    : bolsa_de_palabras_depurada(bolsa_de_palabras_depurada), tamanio_texto(tamanio) {}

ContenidoDepurado::~ContenidoDepurado() {}

std::vector<std::string> ContenidoDepurado::getBolsaDePalabras() const {

    return this->bolsa_de_palabras_depurada;
}

uint32_t ContenidoDepurado::tamanio() const {
    return this->tamanio_texto;
}

herramientas::utiles::Fecha ContenidoDepurado::fecha() const {
    return this->fecha_contenido;
}

std::string ContenidoDepurado::categoria() const {
    return this->categoria_contenido;
}

void ContenidoDepurado::bolsa_de_palabras(const std::vector<std::string>& bolsa_de_palabras_depurada) {
    this->bolsa_de_palabras_depurada = bolsa_de_palabras_depurada;
}

void ContenidoDepurado::tamanio(const uint32_t & tamanio_texto) {
    this->tamanio_texto = tamanio_texto;
}

void ContenidoDepurado::fecha(const herramientas::utiles::Fecha & fecha_contenido) {
    this->fecha_contenido = fecha_contenido;
}

void ContenidoDepurado::categoria(const std::string & categoria_contenido) {
    this->categoria_contenido = categoria_contenido;
}


std::string ContenidoDepurado::getValorAlmacenable() {

    herramientas::utiles::Json json;

    json.agregarAtributoValor("palabras", herramientas::utiles::FuncionesString::unir(this->bolsa_de_palabras_depurada, " "));
    json.agregarAtributoValor("tamanio", this->tamanio_texto);
    json.agregarAtributoValor("fecha", this->fecha_contenido.getStringAAAAMMDD());
    json.agregarAtributoValor("categoria", this->categoria_contenido);

    return json.jsonString();
}

void ContenidoDepurado::asignarNuevoId() {
}

void ContenidoDepurado::parsearValorAlmacenable(std::string valor_almacenable) {
    herramientas::utiles::Json json(valor_almacenable);

    this->bolsa_de_palabras_depurada = herramientas::utiles::FuncionesString::separar(json.getAtributoValorString("palabras"), " ");
    this->tamanio_texto = json.getAtributoValorUint("tamanio");
    this->fecha_contenido = herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(json.getAtributoValorString("fecha"));
    this->categoria_contenido = json.getAtributoValorString("categoria");
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