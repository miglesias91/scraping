#pragma once

// medios digitales
#include <html/include/portal_noticias.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping::extraccion::interfaceo
{

class MedioPortalNoticias : public Medio, public medios::html::portal_noticias
{
public:
    MedioPortalNoticias(herramientas::utiles::Json * json = NULL);
    virtual ~MedioPortalNoticias();

    // GETTERS

    virtual std::string getGrupoMedio();

    // SETTERS

    // METODOS

    virtual Medio * clonar();

    virtual std::string prefijoGrupo();

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IHashable

    virtual unsigned long long int hashcode();

    // CONSULTAS

private:

};

};

