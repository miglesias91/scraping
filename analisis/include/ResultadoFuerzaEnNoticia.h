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
    ResultadoFuerzaEnNoticia(unsigned int maximo_valores_a_almacenar = 20);
    virtual ~ResultadoFuerzaEnNoticia();

    // GETTERS

    virtual float getFuerza(std::string palabra);

    virtual std::vector<std::pair<std::string, float>> getTop(unsigned int cantidad_de_valores_a_recuperar);

    // SETTERS

    // METODOS

    virtual unsigned int cantidadDePalabras();

    static bool compararFuerzasMayorAMenor(std::pair<std::string, float> a, std::pair<std::string, float> b);

    static bool compararFuerzasMenosAMayor(std::pair<std::string, float> a, std::pair<std::string, float> b);

    // metodos de IResultadoTecnica

    virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:

    unsigned int maximo_valores_a_almacenar;

    std::unordered_map<std::string, float> fuerza_por_palabra;
};

};
};
};