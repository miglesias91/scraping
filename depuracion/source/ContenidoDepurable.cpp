#include <depuracion/include/ContenidoDepurable.h>

using namespace scraping::depuracion;

ContenidoDepurable::ContenidoDepurable(scraping::extraccion::Contenido * contenido_a_depurar) : IDepurable(), contenido_a_depurar(contenido_a_depurar) {}

ContenidoDepurable::~ContenidoDepurable() {}

std::string ContenidoDepurable::getTextoDepurable() {
    return this->contenido_a_depurar->getTitulo() + " " + this->contenido_a_depurar->getTitulo() + " " + this->contenido_a_depurar->getTexto();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS