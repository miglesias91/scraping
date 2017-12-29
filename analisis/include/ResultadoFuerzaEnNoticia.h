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

class ResultadoFuerzaEnNoticia : public IResultadoTecnica
{
public:
    ResultadoFuerzaEnNoticia();
    virtual ~ResultadoFuerzaEnNoticia();

    // GETTERS

    // SETTERS

    // METODOS

    virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia);

    // CONSULTAS

private:

    std::unordered_map<std::string, unsigned int> fuerza_por_palabra;
};

};
};
};