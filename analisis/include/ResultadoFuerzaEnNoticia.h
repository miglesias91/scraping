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
    ResultadoFuerzaEnNoticia(unsigned int maximo_valores_a_almacenar = 100);
    virtual ~ResultadoFuerzaEnNoticia();

    // GETTERS

    virtual float getFuerza(std::string palabra);

    virtual std::vector<std::pair<std::string, float>> getFuerzas();

    virtual std::vector<std::pair<std::string, float>> getTop(unsigned int cantidad_de_valores_a_recuperar);

    // getters de IResultadoTecnica

    virtual std::unordered_map<std::string, float> getFuerzaPorPalabra();

    // SETTERS

    // METODOS

    virtual unsigned int cantidadDePalabras();

    // suma la fuerza a la palabra: fuerza_a_sumar = <palabra a modificar, fuerza a agregar>
    // si no se encuentra la palabra, se crea con el valor que se quiere sumar.
    virtual bool sumarFuerza(std::pair<std::string, float> fuerza_a_sumar);

    virtual bool sumarFuerzas(ResultadoFuerzaEnNoticia * fuerzas_a_sumar);

    static bool compararFuerzasMayorAMenor(std::pair<std::string, float> a, std::pair<std::string, float> b);

    static bool compararFuerzasMenosAMayor(std::pair<std::string, float> a, std::pair<std::string, float> b);

    // metodos de IResultadoTecnica

    virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

    virtual bool existePalabra(std::string palabra);

private:

    unsigned int maximo_valores_a_almacenar;

    std::unordered_map<std::string, float> fuerza_por_palabra;
};

};
};
};