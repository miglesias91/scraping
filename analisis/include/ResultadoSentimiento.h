#pragma once

// stl
#include <string>
#include <unordered_map>
#include <iomanip>

// herramientas
#include <utiles/include/FuncionesString.h>

// analisis
#include <analisis/include/IResultadoTecnica.h>

namespace scraping
{
namespace analisis
{
namespace tecnicas
{

class ResultadoSentimiento : public IResultadoTecnica
{
public:
    struct valoracion
    {
        double suma = 0.0f;
        unsigned long long int cantidad = 0;
        
        void leer(const std::string & valoracion_escrita) {
            std::vector<std::string> suma_cantidad = herramientas::utiles::FuncionesString::separar(valoracion_escrita, "/");

            this->suma = std::stod(suma_cantidad[0]);
            this->cantidad = std::stoull(suma_cantidad[1]);
        }

        std::string escribir() {
            std::ostringstream string_stream;
            string_stream << std::setprecision(5) << this->suma;

            return string_stream.str() + "/" + std::to_string(this->cantidad);
        }

        double promedio() {
            if (cantidad) {
                return suma / cantidad;
            }
            else {
                return 0.0f;
            }
        }

        void operator+= (const double & suma) {
            this->suma += suma;
            this->cantidad += 1;
        }

        void operator+= (const valoracion & valoracion_a_sumar) {
            this->suma += valoracion_a_sumar.suma;
            this->cantidad += valoracion_a_sumar.cantidad;
        }
    };

    struct sentimiento
    {
        valoracion positividad;
        valoracion negatividad;
        valoracion neutralidad;

        void leer(const std::string & sentimiento_escrito) {

            std::vector<std::string> valoraciones_escritas = herramientas::utiles::FuncionesString::separar(sentimiento_escrito, "-");

            this->positividad.leer(valoraciones_escritas[0]);
            this->negatividad.leer(valoraciones_escritas[1]);
            this->neutralidad.leer(valoraciones_escritas[2]);
        }

        std::string escribir() {
            return positividad.escribir() + "-" + negatividad.escribir() + "-" + neutralidad.escribir();
        }

        std::string informar() {

            unsigned long long int cantidad_total = this->total();

            if (cantidad_total) {
                std::string promedio_positividad = herramientas::utiles::FuncionesString::toString((positividad.suma / cantidad_total) * 100, 0);
                std::string promedio_negatividad = herramientas::utiles::FuncionesString::toString((negatividad.suma / cantidad_total) * 100, 0);
                std::string promedio_neutralidad = herramientas::utiles::FuncionesString::toString((neutralidad.suma / cantidad_total) * 100, 0);
                return "+" + promedio_positividad + " -" + promedio_negatividad + " n" + promedio_neutralidad;
            }

            std::string string_cero = herramientas::utiles::FuncionesString::toString(0, 0);
            return "+" + string_cero + " -" + string_cero + " n" + string_cero;
        }

        unsigned long long int total() {

            return positividad.cantidad + negatividad.cantidad + neutralidad.cantidad;
        }

        void operator+= (const sentimiento & sentimiento_a_sumar) {
            this->positividad += sentimiento_a_sumar.positividad;
            this->negatividad += sentimiento_a_sumar.negatividad;
            this->neutralidad += sentimiento_a_sumar.neutralidad;
        }
    };

    explicit ResultadoSentimiento(const uint32_t & maximo_valores_a_almacenar = 100);
    virtual ~ResultadoSentimiento();

    // GETTERS

    virtual valoracion positividad(const std::string & palabra);

    virtual valoracion negatividad(const std::string & palabra);

    virtual valoracion neutralidad(const std::string & palabra);

    // SETTERS

    // METODOS

    virtual std::unordered_map<std::string, sentimiento> sentimientos();

    // se aceptan comodines.
    // 'expresion' puede ser una palabra literal o un termino+comodin
    // (por ahora solo reconoce el comodin '*' al final de la palabra)
    virtual sentimiento valores(const std::string expresion);

    virtual void sumar(const std::string & palabra, const sentimiento & valoracion);

    virtual void sumar(ResultadoSentimiento * resultado_a_sumar);

    virtual void aumentarPositividad(const std::string & palabra, double positividad);

    virtual void aumentarNegatividad(const std::string & palabra, double negatividad);

    virtual void aumentarNeutralidad(const std::string & palabra, double neutralidad);

    virtual bool top(std::vector<std::pair<std::string, sentimiento>> * sentimientos_top, const uint32_t & top_max);

    // metodos de IResultadoTecnica

    virtual void filtrar(const std::vector<std::string> & terminos_a_filtrar);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

    virtual bool existePalabra(std::string palabra);

private:

    // metodos privados
    sentimiento sentimiento_comodin(const std::string & comodin);

    // valoracion
    std::unordered_map<std::string, sentimiento> sentimiento_por_palabra;

    uint32_t maximo_valores_a_almacenar;
};

};
};
};