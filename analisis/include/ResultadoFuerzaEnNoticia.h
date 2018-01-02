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

    virtual float getFuerza(std::string palabra);

    virtual std::vector<std::pair<std::string, float>> getTop(unsigned int cantidad_de_valores_a_recuperar = 10);

    // SETTERS

    // METODOS

    virtual unsigned int cantidadDePalabras();

    static bool compararFuerzasMayorAMenor(std::pair<std::string, float> a, std::pair<std::string, float> b);

    // metodos de IResultadoTecnica

    virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia);

    // CONSULTAS

private:

    std::unordered_map<std::string, float> fuerza_por_palabra;
};

};
};
};