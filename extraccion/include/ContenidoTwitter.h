#pragma once

// medios digitales
#include <twitter/include/Tweet.h>

// extraccion
#include <extraccion/include/Contenido.h>

namespace scraping::extraccion::interfaceo {
class ContenidoTwitter : public Contenido, public medios::twitter::Tweet {
public:
    ContenidoTwitter(herramientas::utiles::Json * json = NULL);
    virtual ~ContenidoTwitter();

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

