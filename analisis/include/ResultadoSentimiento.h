#pragma once

// stl
#include <string>
#include <unordered_map>

// analisis
#include <analisis/include/IResultadoTecnica.h>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class ResultadoSentimiento : public IResultadoTecnica
{
public:
    ResultadoSentimiento(float positivo = 0.0f, float negativo = 0.0f);
    virtual ~ResultadoSentimiento();

    // GETTERS

    // SETTERS

    // METODOS

    virtual void sumarPositivo();

    virtual void sumarNegativo();

    // metodos de IResultadoTecnica

    virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:

    // valoracion
    float positivo;
    float negativo;
};

};
};
};