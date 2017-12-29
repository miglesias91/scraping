#pragma once

// stl
#include <string>
#include <unordered_map>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class IResultadoTecnica
{
public:
    IResultadoTecnica();
    virtual ~IResultadoTecnica();

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