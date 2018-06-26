#pragma once

// analisis
#include <analisis/include/ResultadoAnalisis.h>

// preparacion
#include <preparacion/include/ResultadoAnalisisDiario.h>

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

    bool almacenarContenido(scraping::extraccion::Contenido * contenido_a_almacenar) const;

    bool almacenarMedio(scraping::extraccion::Medio * medio_a_almacenar);
    bool almacenarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_almacenar);
    bool almacenarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_almacenar);
    bool almacenarIDActualContenido() const;

    bool recuperarContenido(scraping::extraccion::Contenido * contenido_a_recuperar);
    bool recuperarMedio(scraping::extraccion::Medio * medio_a_recuperar);
    bool recuperarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_recuperar);
    bool recuperarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_recuperar);

    void recuperarIDActualContenido() const;

    // CONSULTAS

private:

};

};
};