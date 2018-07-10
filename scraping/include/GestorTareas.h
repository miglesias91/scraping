#pragma once

// extraccion
#include <extraccion/include/Medio.h>

// analisis
#include <analisis/include/ResultadoAnalisis.h>

// twitter
//#include <twitter/include/Cuenta.h>

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

    static bool extraer_facebook();
    static bool extraer_twitter();
    static bool extraer_portales();

    static bool depurar_facebook();
    static bool depurar_twitter();
    static bool depurar_portales();

    static bool analizar_facebook();
    static bool analizar_twitter();
    static bool analizar_portales();

    static bool preparar_facebook();
    static bool preparar_twitter();
    static bool preparar_portales();

    static void scrapear_facebook();
    static void scrapear_twitter();
    static void scrapear_portales();

private:
};

};
};