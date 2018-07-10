#pragma once

// stl
#include <string>

// medios digitales
#include <noticias/include/noticia.h>

// extraccion
#include <extraccion/include/Contenido.h>

namespace scraping::extraccion::interfaceo {
class ContenidoPortalNoticias : public Contenido, public medios::noticias::noticia {
public:
    ContenidoPortalNoticias(herramientas::utiles::Json * json = nullptr);
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

