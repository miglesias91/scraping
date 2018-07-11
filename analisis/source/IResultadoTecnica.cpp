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

// GETTERS

// SETTERS

// METODOS

// CONSULTAS
