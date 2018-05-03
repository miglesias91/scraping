#pragma once

// analisis
#include <analisis/include/ITecnica.h>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class Sentimiento : public ITecnica
{
public:
    Sentimiento();
    virtual ~Sentimiento();

    // GETTERS

    // SETTERS

    // METODOS

    // metodos ITecnica

    virtual double aplicar(const std::vector<std::string> & bolsa_de_palabras, IResultadoTecnica * resultado);

    // recibe un contenido EN ESPAÑOL analizable y devuelve el valor del sentimiento.
    // La valoración va de 0 (negativo) a 2 (positivo), siendo 1 = sin opinion.
    // El valor de retorno indica valor del sentimiento.
    virtual double aplicar(scraping::analisis::IAnalizable * contenido_analizable, IResultadoTecnica * resultado);

    // CONSULTAS
};

};
};
};

