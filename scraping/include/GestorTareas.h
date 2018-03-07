#pragma once

// extraccion
#include <extraccion/include/Medio.h>

// twitter
#include <twitter/include/Cuenta.h>

namespace scraping
{
namespace aplicacion
{

class GestorTareas
{
public:
    GestorTareas();
    virtual ~GestorTareas();

    // GETTES

    // SETTER

    // METODOS

    // twitter
    static void scrapearTwitter();

    static void depurarYAnalizarTwitter();

    static void prepararYAlmacenarTwitter();

    // facebook
    static void scrapearFacebook();

    static void depurarYAnalizarFacebook();

    static void prepararYAlmacenarFacebook();

    // CONSULTAS

private:

};

};
};