#pragma once

// medios digitales
#include <twitter/include/cuenta.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping::extraccion::interfaceo
{

class MedioTwitter : public Medio, public medios::twitter::cuenta
{
public:
    MedioTwitter(herramientas::utiles::Json * json = NULL);
    virtual ~MedioTwitter();

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

