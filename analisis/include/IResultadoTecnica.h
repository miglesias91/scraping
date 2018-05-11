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

    // chequea si la palabra matchea con 'expresion'.
    // 'expresion' puede ser una palabra literal, o una expresion regular (es decir, puede contener comodines).
    // NOTA: POR AHORA SOLO SOPORTA ASTERISCO AL FINAL.
    //ejemplo: "jubila*" -> matchea con "jubilado", "jubilados", "jubilacion", etc etc. TODO LO QUE EMPIECE CON "jubila".
    virtual bool match(const std::string & palabra, const std::string & expresion);

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