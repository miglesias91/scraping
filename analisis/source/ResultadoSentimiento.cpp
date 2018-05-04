#include <analisis/include/ResultadoSentimiento.h>

// stl
#include <algorithm>
#include <iomanip>
#include <sstream>

// herramientas
#include <utiles/include/FuncionesString.h>

using namespace scraping::analisis::tecnicas;

ResultadoSentimiento::ResultadoSentimiento(float positivo, float negativo) : positivo(positivo), negativo(negativo)
{
}

ResultadoSentimiento::~ResultadoSentimiento()
{
}

// GETTERS

float ResultadoSentimiento::getFuerza(std::string palabra)
{
    if (false == this->existePalabra(palabra))
    {
        return 0.0f;
    }

    return this->fuerza_por_palabra[palabra];
}

std::vector<std::pair<std::string, float>> ResultadoSentimiento::getFuerzas()
{
    std::vector<std::pair<std::string, float>> vector_fuerza_por_palabra(this->fuerza_por_palabra.begin(), this->fuerza_por_palabra.end());

    return vector_fuerza_por_palabra;
}

double ResultadoSentimiento::getFuerzaTotal()
{
    std::vector<std::pair<std::string, float>> vector_fuerza_por_palabra = this->getFuerzas();

    double fuerza_total = 0.0f;
    for (std::vector<std::pair<std::string, float>>::iterator it = vector_fuerza_por_palabra.begin(); it != vector_fuerza_por_palabra.end(); it++)
    {
        fuerza_total += it->second;
    }

    return fuerza_total;
}

std::vector<std::pair<std::string, float>> ResultadoSentimiento::getTop(unsigned int cantidad_de_valores_a_recuperar)
{
    std::vector<std::pair<std::string, float>> vector_fuerza_por_palabra = this->getFuerzas();

    std::sort(vector_fuerza_por_palabra.begin(), vector_fuerza_por_palabra.end(), compararFuerzasMayorAMenor);

    if (vector_fuerza_por_palabra.size() > cantidad_de_valores_a_recuperar)
    {
        vector_fuerza_por_palabra.resize(cantidad_de_valores_a_recuperar);
    }

    return vector_fuerza_por_palabra;
}

// getters de IResultadoTecnica

std::unordered_map<std::string, float> ResultadoSentimiento::getFuerzaPorPalabra()
{
    return this->fuerza_por_palabra;
}

// SETTERS

// METODOS

unsigned int ResultadoSentimiento::cantidadDePalabras()
{
    return this->fuerza_por_palabra.size();
}

float ResultadoSentimiento::sumarFuerza(std::pair<std::string, float> fuerza_a_sumar)
{
    std::string palabra = fuerza_a_sumar.first;
    float fuerza_a_agregar = fuerza_a_sumar.second;

    std::unordered_map<std::string, float>::iterator it_fuerza = this->fuerza_por_palabra.find(palabra);

    if (this->fuerza_por_palabra.end() != it_fuerza)
    {
        float nuevo_valor = it_fuerza->second + fuerza_a_agregar;
        this->fuerza_por_palabra[palabra] = nuevo_valor;
    }
    else
    {
        this->fuerza_por_palabra[palabra] = fuerza_a_agregar;
    }

    return this->fuerza_por_palabra[palabra];
}

unsigned int ResultadoSentimiento::sumarFuerzas(ResultadoSentimiento * fuerza_a_sumar)
{
    std::vector<std::pair<std::string, float>> vector_fuerza_por_palabra = fuerza_a_sumar->getFuerzas();

    for (std::vector<std::pair<std::string, float>>::iterator it = vector_fuerza_por_palabra.begin(); it != vector_fuerza_por_palabra.end(); it++)
    {
        this->sumarFuerza(*it);
    }

    return vector_fuerza_por_palabra.size();
}

bool ResultadoSentimiento::compararFuerzasMayorAMenor(std::pair<std::string, float> a, std::pair<std::string, float> b)
{
    return a.second > b.second;
}

bool ResultadoSentimiento::compararFuerzasMenosAMayor(std::pair<std::string, float> a, std::pair<std::string, float> b)
{
    return a.second < b.second;
}

// metodos de IResultadoTecnica

bool ResultadoSentimiento::agregarResultado(std::string palabra, float fuerza_en_noticia)
{
    if (this->existePalabra(palabra))
    {
        return false;
    }

    this->fuerza_por_palabra[palabra] = fuerza_en_noticia;
    return true;
}

// metodos de IContieneJson

bool ResultadoSentimiento::armarJson()
{
    this->getJson()->reset();

    std::vector<std::pair<std::string, float>> vector_fuerza_por_palabra = this->getTop(maximo_valores_a_almacenar);

    std::vector<std::string> fuerzas_por_palabras;
    for (std::vector<std::pair<std::string, float>>::iterator it = vector_fuerza_por_palabra.begin(); it != vector_fuerza_por_palabra.end(); it++)
    {
        std::ostringstream string_stream;
        string_stream << std::setprecision(5) << it->second;

        std::string registro = it->first + "_" + string_stream.str();
        fuerzas_por_palabras.push_back(registro);
    }

    herramientas::utiles::Json * json = this->getJson();
    json->agregarAtributoArray("valores", fuerzas_por_palabras);

    return true;
}

bool ResultadoSentimiento::parsearJson()
{
    std::vector<std::string> json_fuerzas = this->getJson()->getAtributoArrayString("valores");

    for (std::vector<std::string>::iterator it = json_fuerzas.begin(); it != json_fuerzas.end(); it++)
    {
        std::vector<std::string> campos = herramientas::utiles::FuncionesString::separar(*it, "_");

        std::string termino = campos[0];
        float fuerza = std::stof(campos[1]);

        this->agregarResultado(termino, fuerza);
    }

    return true;
}

// CONSULTAS

bool ResultadoSentimiento::existePalabra(std::string palabra)
{
    if (this->fuerza_por_palabra.end() == this->fuerza_por_palabra.find(palabra))
    {
        return false;
    }

    return true;
}