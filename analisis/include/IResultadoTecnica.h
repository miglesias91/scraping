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

    // virtual std::unordered_map<std::string, float> getFuerzaPorPalabra() = 0;

    // SETTERS

    // METODOS

    // virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia) = 0;

    // CONSULTAS

private:

};

};
};
};