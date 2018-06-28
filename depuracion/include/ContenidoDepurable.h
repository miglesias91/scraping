#pragma once

// stl
#include <string>

// extraccion
#include <extraccion/include/Contenido.h>

// depuracion
#include <depuracion/include/IDepurable.h>

namespace scraping
{
namespace depuracion
{

class ContenidoDepurable : public IDepurable
{
public:
    ContenidoDepurable(scraping::extraccion::Contenido * contenido_a_depurar = NULL);
    virtual ~ContenidoDepurable();

    // GETTERS
    
    virtual std::string getTextoDepurable();

    // SETTERS

    // METODOS

    // CONSULTAS

private:

    scraping::extraccion::Contenido * contenido_a_depurar;
};

};
};


