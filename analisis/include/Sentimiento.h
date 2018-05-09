#pragma once

// clasificacion
#include <clasificacion-de-texto/include/Clasificador.h>
#include <clasificacion-de-texto/include/Vocabulario.h>

// analisis
#include <analisis/include/ITecnica.h>
#include <analisis/include/ResultadoSentimiento.h>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class Sentimiento : public ITecnica
{
public:

    struct configuracion
    {
        struct red_neuronal
        {
            std::string path_red;
            std::string path_mapa;
        };

        std::string path_vocabulario;
        red_neuronal clasificador_dos_clases;
        red_neuronal clasificador_tres_clases;
    };

    Sentimiento();
    virtual ~Sentimiento();

    // GETTERS

    // SETTERS

    // METODOS

    static bool cargar(const configuracion & configuracion_sentimiento);
    static bool cargar(const std::string & path_configuracion_sentimiento);

    static bool liberar();

    // metodos ITecnica

    virtual void aplicar(const std::vector<std::string> & bolsa_de_palabras, IResultadoTecnica * resultado);

    // recibe un contenido EN ESPAÑOL analizable y devuelve el valor del sentimiento.
    // contiene dos valores: uno para la valoracion positiva y otro para la negativa. Los dos valores van de 0 a 1.
    // El valor de retorno indica valor del sentimiento (si es negativo, el valor es negativo).
    virtual void aplicar(scraping::analisis::IAnalizable * contenido_analizable, IResultadoTecnica * resultado);

    // CONSULTAS

private:

    static ia::clasificacion::Vocabulario vocabulario;
    static ia::clasificacion::Clasificador clasificador_tres_clases;
    static ia::clasificacion::Clasificador clasificador_dos_clases;

    static std::string positivo;
    static std::string negativo;
    static std::string neutral;
};

};
};
};

