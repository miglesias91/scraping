#include <analisis/include/IResultadoTecnica.h>

// herramientas
#include <utiles/include/FuncionesString.h>

using namespace scraping::analisis::tecnicas;

IResultadoTecnica::IResultadoTecnica() : IContieneJson()
{
}

IResultadoTecnica::~IResultadoTecnica()
{
}

bool IResultadoTecnica::match(const std::string & palabra, const std::string & expresion)
{
    if ('*' == *(expresion.end() - 1))
    {
        std::string comienzo_de_palabra(expresion.begin(), expresion.end() - 1);
        return herramientas::utiles::FuncionesString::empiezaCon(palabra, comienzo_de_palabra);
    }

    return palabra == expresion;
}

//std::unordered_map<std::string, unsigned int> IResultadoTecnica::getFuerzaPorPalabra()
//{
//    return this->fuerza_por_palabra;
//}

// GETTERS

// SETTERS

// METODOS

//bool IResultadoTecnica::agregarResultado(std::string palabra, float fuerza_en_noticia)
//{
//    if (this->fuerza_por_palabra.end() != this->fuerza_por_palabra.find(palabra))
//    {
//        return false;
//    }
//
//    this->fuerza_por_palabra[palabra] = fuerza_en_noticia;
//    return true;
//}

// CONSULTAS
