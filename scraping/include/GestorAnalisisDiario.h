#pragma once

// extraccion
#include <extraccion/include/Contenido.h>
#include <extraccion/include/Medio.h>

namespace scraping
{
namespace aplicacion
{

class GestorAnalisisDiario
{
public:
    GestorAnalisisDiario();
    virtual ~GestorAnalisisDiario();

    // GETTES

    // SETTER

    // METODOS

    bool almacenarContenidoParaAnalizar(scraping::extraccion::Contenido * contenido_a_almacenar);

    bool almacenarMedioConContenidoParaAnalizar(scraping::extraccion::Medio * medio_a_almacenar);

    // CONSULTAS

private:

};

};
};