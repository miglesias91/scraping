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
    ResultadoFuerzaEnNoticia(uint32_t maximo_valores_a_almacenar = 300);
    virtual ~ResultadoFuerzaEnNoticia();

    // GETTERS

    // se aceptan comodines.
    // 'expresion' puede ser una palabra literal o un termino+comodin
    // (por ahora solo reconoce el comodin '*' al final de la palabra)
    virtual float getFuerza(std::string expresion);

    virtual std::vector<std::pair<std::string, float>> getFuerzas();
    
    virtual double getFuerzaTotal();

    virtual std::vector<std::pair<std::string, float>> getTop(uint32_t cantidad_de_valores_a_recuperar);

    // getters de IResultadoTecnica

    virtual std::unordered_map<std::string, float> getFuerzaPorPalabra();

    // SETTERS

    // METODOS

    virtual uint32_t cantidadDePalabras();

    // suma la fuerza a la palabra: fuerza_a_sumar = <palabra a modificar, fuerza a agregar>
    // si no se encuentra la palabra, se crea con el valor que se quiere sumar.
    // devuelve el valor de la fuerza actualizado.
    virtual float sumarFuerza(std::pair<std::string, float> fuerza_a_sumar);

    // suma las fuerzas de cada palabra.
    // devuelve la cantida de fuerzas sumadas.
    virtual uint32_t sumarFuerzas(ResultadoFuerzaEnNoticia * fuerzas_a_sumar);

    static bool compararFuerzasMayorAMenor(std::pair<std::string, float> a, std::pair<std::string, float> b);

    static bool compararFuerzasMenosAMayor(std::pair<std::string, float> a, std::pair<std::string, float> b);

    virtual bool agregarResultado(std::string palabra, float fuerza_en_noticia);

    // metodos de IResultadoTecnica

    virtual void filtrar(const std::vector<std::string> & terminos_a_filtrar);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

    virtual bool existePalabra(std::string palabra);

private:

    // metodos privados

    double fuerza_comodin(const std::string & comodin);

    // atributos

    uint32_t maximo_valores_a_almacenar;

    std::unordered_map<std::string, float> fuerza_por_palabra;
};

};
};
};