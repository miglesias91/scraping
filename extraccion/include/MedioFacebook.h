#pragma once

// medios digitales
#include <facebook/include/Aplicacion.h>
#include <facebook/include/Pagina.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping{ namespace extraccion { namespace interfaceo {
class MedioFacebook : public Medio {
public:
    explicit MedioFacebook(const std::string & nombre_pagina);
    explicit MedioFacebook(herramientas::utiles::Json * json = nullptr);
    virtual ~MedioFacebook();

    // GETTERS

    virtual std::string getGrupoMedio();
    virtual std::string etiqueta() const;

    virtual medios::facebook::Pagina * pagina() const;
    virtual herramientas::utiles::Fecha fecha_ultima_publicacion() const;

    // SETTERS

    virtual void pagina(medios::facebook::Pagina * pagina_facebook);
    virtual void fecha_ultima_publicacion(const herramientas::utiles::Fecha & fecha);

    // METODOS

    virtual bool descargar_publicaciones(const medios::facebook::aplicacion & app);

    virtual Medio * clonar();

    virtual std::string prefijoGrupo();

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IHashable

    virtual unsigned long long int hashcode();

    // CONSULTAS

private:

    medios::facebook::Pagina * pagina_facebook;

    herramientas::utiles::Fecha fecha_ultima_publicacion_analizada;
};
};
};

};

