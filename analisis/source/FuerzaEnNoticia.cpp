#include <analisis/include/FuerzaEnNoticia.h>

// stl
#include <unordered_map>

using namespace scraping::analisis::tecnicas;

FuerzaEnNoticia::FuerzaEnNoticia()
{
}

FuerzaEnNoticia::~FuerzaEnNoticia()
{
}

ResultadoFuerzaEnNoticia FuerzaEnNoticia::aplicar(std::vector<std::string> bolsa_de_palabras)
{
    unsigned int cantidad_de_caracteres_en_bolsa_de_palabras = 0;
    std::unordered_map<std::string, unsigned int> cantidad_de_apariciones_por_palabra;

    // 1ero: calculo la cantidad de caracteres en la bolsa de palabras + cuento cuantas veces aparece cada palabra en la bolsa.
    for (std::vector<std::string>::iterator it_bolsa = bolsa_de_palabras.begin(); it_bolsa != bolsa_de_palabras.end(); it_bolsa++)
    {
        cantidad_de_caracteres_en_bolsa_de_palabras += it_bolsa->size();

        std::unordered_map<std::string, unsigned int>::iterator it_apariciones = cantidad_de_apariciones_por_palabra.find(*it_bolsa);

        if (cantidad_de_apariciones_por_palabra.end() != it_apariciones)
        {
            unsigned int nuevo_valor = it_apariciones->second + 1;
            cantidad_de_apariciones_por_palabra[*it_bolsa] = nuevo_valor;
        }
        else
        {
            cantidad_de_apariciones_por_palabra[*it_bolsa] = 1;
        }
    }

    float factor_tamanio_de_bolsa = std::log10(cantidad_de_caracteres_en_bolsa_de_palabras);

    // 2do: calculo la fuerza de cada palabra en la bolsa de palabras
    std::vector<std::pair<std::string, float>> fuerzas_por_palabra;
    ResultadoFuerzaEnNoticia resultado;
    for (std::unordered_map<std::string, unsigned int>::iterator it_apariciones = cantidad_de_apariciones_por_palabra.begin(); it_apariciones != cantidad_de_apariciones_por_palabra.end(); it_apariciones++)
    {
        unsigned int cantidad_de_apariciones = it_apariciones->second;

        float fuerza_palabra_en_bolsa = factor_tamanio_de_bolsa * cantidad_de_apariciones;

        std::pair<std::string, float> nuevo_par(it_apariciones->first, fuerza_palabra_en_bolsa);

        fuerzas_por_palabra.push_back(nuevo_par);

        resultado.agregarResultado(it_apariciones->first, fuerza_palabra_en_bolsa);
    }

    return fuerzas_por_palabra;
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS