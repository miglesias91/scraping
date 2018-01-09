#include <depuracion/include/ContenidoDepurable.h>

using namespace scraping::depuracion;

ContenidoDepurable::ContenidoDepurable(scraping::extraccion::Contenido * contenido_a_depura) : IDepurable(), contenido_a_depura(contenido_a_depura)
{
}

ContenidoDepurable::~ContenidoDepurable()
{
}

std::string ContenidoDepurable::getTextoDepurable()
{
    return this->contenido_a_depura->getTexto();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS