#include <facebook/include/Publicacion.h>

// stl
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

// herramientas
#include <utiles/include/Conversiones.h>
#include <utiles/include/FuncionesString.h>

using namespace scraping::facebook::modelo;

Publicacion::Publicacion(herramientas::utiles::Json * publicacion_json) : Contenido(publicacion_json)
{
    if (NULL == publicacion_json)
    {
        return;
    }

    std::string id_pagina_id_publicacion = this->getJson()->getAtributoValorString("id");
    std::string fecha_creacion_formato_facebook = this->getJson()->getAtributoValorString("created_time");
    std::string texto = this->getJson()->getAtributoValorString("message");

    std::vector<std::string> ids = herramientas::utiles::FuncionesString::separar(id_pagina_id_publicacion, "_");

    this->setIdPublicacion(std::stoull(ids[1]));
    this->setFechaCreacion(this->parsearFechaEnFormatoFacebook(fecha_creacion_formato_facebook));
    this->setTextoPublicacion(texto);
    this->setIdPagina(std::stoull(ids[0]));
}

Publicacion::~Publicacion()
{
}

// GETTERS

unsigned long long int Publicacion::getIdPublicacion()
{
    return this->id_publicacion;
}

unsigned long long int Publicacion::getIdPagina()
{
    return this->id_pagina;
}

herramientas::utiles::Fecha Publicacion::getFechaCreacion()
{
    return this->fecha_creacion;
}

std::string Publicacion::getTextoPublicacion()
{
    return this->texto_publicacion;
}

// SETTERS

void Publicacion::setIdPublicacion(unsigned long long int id_publicacion)
{
    this->id_publicacion = id_publicacion;
}

void Publicacion::setIdPagina(unsigned long long int id_pagina)
{
    this->id_pagina = id_pagina;
}

void Publicacion::setFechaCreacion(herramientas::utiles::Fecha fecha_creacion)
{
    this->fecha_creacion = fecha_creacion;

    this->Contenido::setFecha(fecha_creacion);
}

void Publicacion::setTextoPublicacion(std::string texto_publicacion)
{
    this->texto_publicacion = texto_publicacion;

    this->Contenido::setTexto(texto_publicacion);
}

// METODOS

// metodos de IContieneJson

bool Publicacion::armarJson()
{
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("id_publicacion", this->getIdPublicacion());
    this->getJson()->agregarAtributoValor("fecha_creacion", this->getFechaCreacion().getStringAAAAMMDDHHmmSS());
    this->getJson()->agregarAtributoValor("texto_publicacion", this->getTextoPublicacion());
    this->getJson()->agregarAtributoValor("id_pagina", this->getIdPagina());

    return true;
}

bool Publicacion::parsearJson()
{
    unsigned long long int id_publicacion = this->getJson()->getAtributoValorUint("id_publicacion");
    std::string fecha_creacion = this->getJson()->getAtributoValorString("fecha_creacion");
    std::string texto_publicacion = this->getJson()->getAtributoValorString("texto_publicacion");
    unsigned long long int id_pagina = this->getJson()->getAtributoValorUint("id_pagina");

    this->setIdPublicacion(id_publicacion);
    this->setFechaCreacion(herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(fecha_creacion));
    this->setTextoPublicacion(texto_publicacion);
    this->setIdPagina(id_pagina);

    return true;
}

// CONSULTAS

// OPERADORES

// METODOS PRIVADOS

herramientas::utiles::Fecha Publicacion::parsearFechaEnFormatoFacebook(std::string fecha_formato_facebook)
{
    herramientas::utiles::Fecha fecha;
    // la fecha viene en formato "2015-06-28T11:24:43+0000" --> le borro los "+0000 "
    // para que me quede "2015-06-28T11:24:43" y la pueda parsear bien.
    size_t posicion_signo_mas = fecha_formato_facebook.find_first_of('+');

    fecha_formato_facebook.erase(posicion_signo_mas, 5);

    std::stringstream stream_fecha(fecha_formato_facebook);

    std::tm t = {};
    stream_fecha >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");

    if (stream_fecha.fail())
    {
        std::cout << "Fecha formato error.\n";
    }
    else
    {
        fecha.setAnio(t.tm_year + 1900);
        fecha.setMes(t.tm_mon + 1);
        fecha.setDia(t.tm_mday);

        fecha.setHoras(t.tm_hour);
        fecha.setMinutos(t.tm_min);
        fecha.setSegundos(t.tm_sec);
    }

    return fecha;
}