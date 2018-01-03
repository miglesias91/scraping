#include <analisis/include/ResultadoFuerzaEnNoticia.h>

// stl
#include <algorithm>

using namespace scraping::analisis::tecnicas;

ResultadoFuerzaEnNoticia::ResultadoFuerzaEnNoticia(unsigned int maximo_valores_a_almacenar) : IResultadoTecnica(), maximo_valores_a_almacenar(maximo_valores_a_almacenar)
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

    if (vector_fuerza_por_palabra.size() > cantidad_de_valores_a_recuperar)
    {
        vector_fuerza_por_palabra.resize(cantidad_de_valores_a_recuperar);
    }

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

bool ResultadoFuerzaEnNoticia::armarJson()
{
    this->getJson()->reset();

    herramientas::utiles::Json * json = this->getJson();
    std::vector<std::pair<std::string, float>> vector_fuerza_por_palabra = this->getTop(maximo_valores_a_almacenar);

    for (std::vector<std::pair<std::string, float>>::iterator it = vector_fuerza_por_palabra.begin(); it != vector_fuerza_por_palabra.end(); it++)
    {
        json->agregarAtributoValor(it->first, it->second);
    }

    return true;
}

bool ResultadoFuerzaEnNoticia::parsearJson()
{
    return false;
}

unsigned int ResultadoFuerzaEnNoticia::cantidadDePalabras()
{
    return this->fuerza_por_palabra.size();
}

bool ResultadoFuerzaEnNoticia::compararFuerzasMayorAMenor(std::pair<std::string, float> a, std::pair<std::string, float> b)
{
    return a.second > b.second;
}

bool ResultadoFuerzaEnNoticia::compararFuerzasMenosAMayor(std::pair<std::string, float> a, std::pair<std::string, float> b)
{
    return a.second < b.second;
}

// CONSULTAS
