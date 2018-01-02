#include <analisis/include/ResultadoFuerzaEnNoticia.h>

// stl
#include <algorithm>

using namespace scraping::analisis::tecnicas;

ResultadoFuerzaEnNoticia::ResultadoFuerzaEnNoticia() : IResultadoTecnica()
{
}

ResultadoFuerzaEnNoticia::~ResultadoFuerzaEnNoticia()
{
}

float ResultadoFuerzaEnNoticia::getFuerza(std::string palabra)
{
    return this->fuerza_por_palabra[palabra];
}

std::vector<std::pair<std::string, float>> ResultadoFuerzaEnNoticia::getTop(unsigned int cantidad_de_valores_a_recuperar)
{
    std::vector<std::pair<std::string, float>> vector_fuerza_por_palabra(this->fuerza_por_palabra.begin(), this->fuerza_por_palabra.end());

    std::sort(vector_fuerza_por_palabra.begin(), vector_fuerza_por_palabra.end(), compararFuerzasMayorAMenor);

    vector_fuerza_por_palabra.resize(cantidad_de_valores_a_recuperar);

    return vector_fuerza_por_palabra;
}

// GETTERS

// SETTERS

// METODOS

bool ResultadoFuerzaEnNoticia::agregarResultado(std::string palabra, float fuerza_en_noticia)
{
    if (this->fuerza_por_palabra.end() != this->fuerza_por_palabra.find(palabra))
    {
        return false;
    }

    this->fuerza_por_palabra[palabra] = fuerza_en_noticia;
    return true;
}

unsigned int ResultadoFuerzaEnNoticia::cantidadDePalabras()
{
    return this->fuerza_por_palabra.size();
}

bool ResultadoFuerzaEnNoticia::compararFuerzasMayorAMenor(std::pair<std::string, float> a, std::pair<std::string, float> b)
{
    return a.second > b.second;
}

// CONSULTAS
