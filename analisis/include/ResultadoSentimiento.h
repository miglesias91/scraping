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
    ResultadoSentimiento(unsigned int maximo_valores_a_almacenar = 100);
    virtual ~ResultadoSentimiento();

    // GETTERS

    // SETTERS

    // METODOS

    // metodos de IResultadoTecnica

    virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:

    // valoracion
    float valoracion;
};

};
};
};