#pragma once

// medios digitales
#include <facebook/include/publicacion.h>

// extraccion
#include <extraccion/include/Contenido.h>

namespace scraping::extraccion::interfaceo
{

class ContenidoFacebook : public Contenido, public medios::facebook::publicacion
{
public:
    ContenidoFacebook(herramientas::utiles::Json * json = NULL);
    virtual ~ContenidoFacebook();

    // GETTERS

    // SETTERS

    // METODOS

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:
};

};

