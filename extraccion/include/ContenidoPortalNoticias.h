#pragma once

// stl
#include <string>

// medios digitales
#include <html/include/noticia.h>

// extraccion
#include <extraccion/include/Contenido.h>

namespace scraping::extraccion::interfaceo
{

class ContenidoPortalNoticias : public Contenido, public medios::html::noticia
{
public:
    ContenidoPortalNoticias(herramientas::utiles::Json * json = NULL);
    virtual ~ContenidoPortalNoticias();

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

