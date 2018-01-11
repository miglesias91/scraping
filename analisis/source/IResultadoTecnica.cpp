#include <analisis/include/IResultadoTecnica.h>

using namespace scraping::analisis::tecnicas;

IResultadoTecnica::IResultadoTecnica() : IContieneJson()
{
}

IResultadoTecnica::~IResultadoTecnica()
{
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
