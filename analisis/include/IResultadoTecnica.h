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

    // filtra terminos por id. (es decir, elimina todos losterminos que no esten incluidos en los ids pasados parametro).
    // los terminos a filtrar ACEPTAN COMODINES ('*' al final de la palabra).
    virtual void filtrar(const std::vector<std::string> & terminos_a_filtrar) = 0;

    // virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia) = 0;

    // CONSULTAS

private:

};

};
};
};