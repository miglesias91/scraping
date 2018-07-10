#pragma once

// stl
#include <mutex>

// analisis
#include <analisis/include/ResultadoAnalisis.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping
{
namespace preparacion
{

class Preparador
{
public:
    Preparador();
    virtual ~Preparador();

    // GETTERS

    // SETTERS

    // METODOS

    //virtual bool preparar_twitter() const;
    //virtual bool preparar_facebook() const;
    //virtual bool preparar_portales() const;

    virtual bool preparar(scraping::extraccion::Medio * medio) const;

    virtual bool combinar(std::vector<scraping::analisis::ResultadoAnalisis*> resultados_a_combinar, scraping::analisis::ResultadoAnalisis * resultado_combinacion) const;

    // CONSULTAS

private:

    static std::mutex mutex_modificacion_resultado_diario;
};

};
};


