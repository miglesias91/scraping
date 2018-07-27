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

    bool recuperar(scraping::IAlmacenable * contenido_a_recuperar) const;
    bool almacenar(scraping::IAlmacenable * contenido_a_almacenar) const;
    bool modificar(scraping::IAlmacenable * contenido_a_modificar) const;

    bool recuperarContenido(scraping::IAlmacenable * contenido_a_recuperar) const;
    bool almacenarContenido(scraping::IAlmacenable * contenido_a_almacenar) const;
    bool modificarContenido(scraping::IAlmacenable * contenido_a_modificar) const;

    bool almacenarMedio(scraping::extraccion::Medio * medio_a_almacenar) const;
    bool almacenarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_almacenar) const;
    bool almacenarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_almacenar) const;
    bool almacenarIDActualContenido() const;

    //bool recuperarContenido(scraping::extraccion::Contenido * contenido_a_recuperar) const;
    bool recuperarMedio(scraping::extraccion::Medio * medio_a_recuperar) const;
    bool recuperarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_recuperar) const;
    bool recuperarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_recuperar) const;

    bool modificarMedio(scraping::extraccion::Medio * medio_a_almacenar) const;
    bool modificarResultadoAnalisis(scraping::analisis::ResultadoAnalisis * resultado_a_almacenar) const;
    bool modificarResultadoAnalisisDiario(scraping::preparacion::ResultadoAnalisisDiario * resultado_a_almacenar) const;

    void recuperarIDActualContenido() const;

    // CONSULTAS

private:

};

};
};