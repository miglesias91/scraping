#include <extraccion/include/Contenido.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

namespace scraping::extraccion {

herramientas::utiles::GestorIDs Contenido::gestor_ids_contenidos;

Contenido::Contenido(const std::string & titulo, const std::string & texto, const std::string & categoria, const herramientas::utiles::Fecha & fecha)
    : IAlmacenable(ConfiguracionScraping::prefijoContenido()), IContieneJson(nullptr),
    titulo(titulo), texto(texto), categoria(categoria), fecha(fecha) {}

Contenido::Contenido(herramientas::utiles::Json * json) : IAlmacenable(ConfiguracionScraping::prefijoContenido()), IContieneJson(json) {}

Contenido::~Contenido() {}

// GETTERS

herramientas::utiles::Fecha Contenido::getFecha() const {
    return this->fecha;
}

std::string Contenido::getTitulo() const {
    return this->titulo;
}

std::string Contenido::getTexto() const {
    return this->texto;
}

std::string Contenido::getCategoria() const {
    return this->categoria;
}


std::string Contenido::getClaveIDActual() {
    return ConfiguracionScraping::claveIDContenidoActual();
}

herramientas::utiles::GestorIDs * Contenido::getGestorIDs() {
    return &gestor_ids_contenidos;
}

// getters de IAlmacenable
std::string Contenido::getValorAlmacenable()
{
    this->armarJson();

    herramientas::utiles::Json json_almacenable;

    // agrego el texto.
    // json_almacenable.agregarAtributoValor("texto_contenido", this->getTexto());

    // seteo la info del medio.
    herramientas::utiles::Json* json_info_contenido = this->getJson();
    json_almacenable.agregarAtributoJson("info_contenido", json_info_contenido);

    std::string string_almacenable = json_almacenable.jsonString();

    return string_almacenable;
}

// SETTERS

void Contenido::setTexto(const std::string & texto) {
    this->texto = texto;
}

void Contenido::setTitulo(const std::string & titulo) {
    this->titulo = titulo;
}

void Contenido::setCategoria(const std::string & categoria) {
    this->categoria = categoria;
}

void Contenido::setFecha(const herramientas::utiles::Fecha & fecha) {
    this->fecha = fecha;
}
// METODOS

// metodos de IAlmacenable

void Contenido::asignarNuevoId()
{
    this->setId(gestor_ids_contenidos.nuevoID());
}

void Contenido::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json json_almacenable(valor_almacenable);

    // parseo los ids no analizados.
    // this->texto = json_almacenable.getAtributoValorString("texto_contenido");

    // parseo contenido
    herramientas::utiles::Json* json_info_contenido = json_almacenable.getAtributoValorJson("info_contenido");

    this->setJson(json_info_contenido);
    this->parsearJson();
}

std::string Contenido::prefijoGrupo() {
    return ConfiguracionScraping::prefijoContenido();
}

// metodos de IContieneJson

bool Contenido::armarJson() {

    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("titulo", this->titulo);
    this->getJson()->agregarAtributoValor("texto", this->texto);
    this->getJson()->agregarAtributoValor("categoria", this->categoria);
    this->getJson()->agregarAtributoValor("fecha", this->fecha.getStringAAAAMMDDHHmmSS());

    return true;
}

bool Contenido::parsearJson() {
    std::string titulo = this->getJson()->getAtributoValorString("titulo");
    std::string texto = this->getJson()->getAtributoValorString("texto");
    std::string categoria = this->getJson()->getAtributoValorString("categoria");
    std::string string_fecha = this->getJson()->getAtributoValorString("fecha");

    this->setTitulo(titulo);
    this->setTexto(texto);
    this->setCategoria(categoria);
    this->setFecha(herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(string_fecha));

    return true;
}

}