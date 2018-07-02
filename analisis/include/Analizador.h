#pragma once

// extraccion
#include <extraccion/include/Medio.h>

// analisis
#include <analisis/include/IAnalizable.h>
#include <analisis/include/ResultadoAnalisis.h>

namespace scraping
{
namespace analisis
{

class Analizador
{
public:
    Analizador();
    virtual ~Analizador();

    // GETTERS

    // SETTERS

    // METODOS

    virtual bool analizar_twitter() const;
    virtual bool analizar_facebook() const;
    virtual bool analizar_portales() const;

    virtual bool analizar(extraccion::Medio * medio) const;

    virtual void analizar(IAnalizable * contenido_a_analizar, ResultadoAnalisis * resultado_analisis) const;

    // CONSULTAS

private:
};

};
};


