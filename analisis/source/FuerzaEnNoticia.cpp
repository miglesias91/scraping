#include <analisis/include/FuerzaEnNoticia.h>

// stl
#include <unordered_map>

// scraping
#include <scraping/include/Logger.h>

namespace scraping {
    namespace analisis {
        namespace tecnicas {

FuerzaEnNoticia::FuerzaEnNoticia(float fuerza_minima) : fuerza_minima(fuerza_minima)
{
}

FuerzaEnNoticia::~FuerzaEnNoticia()
{
}

void FuerzaEnNoticia::aplicar(const std::vector<std::string> & bolsa_de_palabras, IResultadoTecnica * resultado)
{
    ResultadoFuerzaEnNoticia * resultado_fza_en_noticia = static_cast<ResultadoFuerzaEnNoticia*>(resultado);

    uint32_t cantidad_de_caracteres_en_bolsa_de_palabras = 0;
    std::unordered_map<std::string, uint32_t> cantidad_de_apariciones_por_termino;

    // 1ero: calculo la cantidad de caracteres en la bolsa de palabras + cuento cuantas veces aparece cada palabra en la bolsa.
    std::vector<std::string>::const_iterator it_segunda_palabra = bolsa_de_palabras.cbegin() + 1;
    std::vector<std::string>::const_iterator it_tercera_palabra = bolsa_de_palabras.cbegin() + 2;
    for (std::vector<std::string>::const_iterator it_bolsa = bolsa_de_palabras.cbegin(); it_bolsa != bolsa_de_palabras.cend(); it_bolsa++) {
        cantidad_de_caracteres_en_bolsa_de_palabras += it_bolsa->size();

        std::string una_palabra = *it_bolsa;
        this->nueva_aparicion(&cantidad_de_apariciones_por_termino, una_palabra);

        std::string dos_palabras = "";
        if (bolsa_de_palabras.cend() != it_segunda_palabra) {
            dos_palabras = una_palabra + " " + *it_segunda_palabra;

            this->nueva_aparicion(&cantidad_de_apariciones_por_termino, dos_palabras);
            it_segunda_palabra++;
        }

        std::string tres_palabras = "";
        if (bolsa_de_palabras.cend() != it_tercera_palabra) {
            tres_palabras = dos_palabras + " " + *it_tercera_palabra;

            this->nueva_aparicion(&cantidad_de_apariciones_por_termino, tres_palabras);
            it_tercera_palabra++;
        }
    }

    float factor_tamanio_de_bolsa = std::log10(cantidad_de_caracteres_en_bolsa_de_palabras);

    // 2do: calculo la fuerza de cada palabra en la bolsa de palabras
    for (std::unordered_map<std::string, uint32_t>::iterator it_apariciones = cantidad_de_apariciones_por_termino.begin(); it_apariciones != cantidad_de_apariciones_por_termino.end(); it_apariciones++)
    {
        uint32_t cantidad_de_apariciones = it_apariciones->second;

        float fuerza_palabra_en_bolsa = factor_tamanio_de_bolsa * cantidad_de_apariciones;

        if (fuerza_palabra_en_bolsa > this->fuerza_minima)
        {
            resultado_fza_en_noticia->agregarResultado(it_apariciones->first, fuerza_palabra_en_bolsa);
        }
    }
}

void FuerzaEnNoticia::aplicar(scraping::analisis::IAnalizable * contenido_analizable, IResultadoTecnica * resultado)
{
    ResultadoFuerzaEnNoticia * resultado_fza_en_noticia = static_cast<ResultadoFuerzaEnNoticia*>(resultado);

    uint32_t cantidad_de_caracteres_en_bolsa_de_palabras = 0;
    std::unordered_map<std::string, uint32_t> cantidad_de_apariciones_por_termino;

    std::vector<std::string> bolsa_de_palabras = contenido_analizable->getBolsaDePalabras();

    // 1ero: calculo la cantidad de caracteres en la bolsa de palabras + cuento cuantas veces aparece cada palabra en la bolsa.
    std::vector<std::string>::const_iterator it_segunda_palabra = bolsa_de_palabras.cbegin() + 1;
    std::vector<std::string>::const_iterator it_tercera_palabra = bolsa_de_palabras.cbegin() + 2;
    for (std::vector<std::string>::const_iterator it_bolsa = bolsa_de_palabras.cbegin(); it_bolsa != bolsa_de_palabras.cend(); it_bolsa++) {
        cantidad_de_caracteres_en_bolsa_de_palabras += it_bolsa->size();

        std::string una_palabra = *it_bolsa;
        this->nueva_aparicion(&cantidad_de_apariciones_por_termino, una_palabra);

        std::string dos_palabras = "";
        if (bolsa_de_palabras.cend() != it_segunda_palabra) {
            dos_palabras = una_palabra + " " + *it_segunda_palabra;

            this->nueva_aparicion(&cantidad_de_apariciones_por_termino, dos_palabras);
            it_segunda_palabra++;
        }

        std::string tres_palabras = "";
        if (bolsa_de_palabras.cend() != it_tercera_palabra) {
            tres_palabras = dos_palabras + " " + *it_tercera_palabra;

            this->nueva_aparicion(&cantidad_de_apariciones_por_termino, tres_palabras);
            it_tercera_palabra++;
        }
    }

    float factor_tamanio_de_bolsa = std::log10(contenido_analizable->getTamanio());

    // 2do: calculo la fuerza de cada palabra en la bolsa de palabras
    for (std::unordered_map<std::string, uint32_t>::iterator it_apariciones = cantidad_de_apariciones_por_termino.begin(); it_apariciones != cantidad_de_apariciones_por_termino.end(); it_apariciones++)
    {
        uint32_t cantidad_de_apariciones = it_apariciones->second;

        float fuerza_palabra_en_bolsa = factor_tamanio_de_bolsa * cantidad_de_apariciones;

        if (fuerza_palabra_en_bolsa > this->fuerza_minima)
        {
            resultado_fza_en_noticia->agregarResultado(it_apariciones->first, fuerza_palabra_en_bolsa);
        }
    }
}

void FuerzaEnNoticia::nueva_aparicion(std::unordered_map<std::string, uint32_t>* cantidad_de_apariciones_por_termino, const std::string & termino) {
    if (cantidad_de_apariciones_por_termino->count(termino)) {
        uint32_t nuevo_valor = (*cantidad_de_apariciones_por_termino)[termino] + 1;
        (*cantidad_de_apariciones_por_termino)[termino] = nuevo_valor;
    }
    else {
        (*cantidad_de_apariciones_por_termino)[termino] = 1;
    }
}
}
}
}