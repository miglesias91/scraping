#pragma once

// medios digitales
#include <facebook/include/pagina.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping::extraccion::interfaceo
{

class MedioFacebook : public Medio, public medios::facebook::pagina
{
public:
    MedioFacebook(herramientas::utiles::Json * json = NULL);
    virtual ~MedioFacebook();

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

