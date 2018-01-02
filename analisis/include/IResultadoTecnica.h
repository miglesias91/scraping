#pragma once

// stl
#include <string>
#include <unordered_map>

// herramientas
#include <utiles/include/IContieneJson.h>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class IResultadoTecnica : public herramientas::utiles::IContieneJson
{
public:
    IResultadoTecnica();
    virtual ~IResultadoTecnica();

    // GETTERS

    std::unordered_map<std::string, unsigned int> getFuerzaPorPalabra();

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