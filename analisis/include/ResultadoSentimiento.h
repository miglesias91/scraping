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
        double suma;
        unsigned long long int cantidad;
        
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

        void operator+= (const sentimiento & sentimiento_a_sumar) {
            this->positividad += sentimiento_a_sumar.positividad;
            this->negatividad += sentimiento_a_sumar.negatividad;
            this->neutralidad += sentimiento_a_sumar.neutralidad;
        }
    };

    ResultadoSentimiento();
    virtual ~ResultadoSentimiento();

    // GETTERS

    virtual valoracion positividad(const std::string & palabra);

    virtual valoracion negatividad(const std::string & palabra);

    virtual valoracion neutralidad(const std::string & palabra);

    // SETTERS

    // METODOS

    virtual std::unordered_map<std::string, sentimiento> sentimientos();

    virtual void sumar(const std::string & palabra, const sentimiento & valoracion);

    virtual void sumar(ResultadoSentimiento * resultado_a_sumar);

    virtual void aumentarPositividad(const std::string & palabra, double positividad);

    virtual void aumentarNegatividad(const std::string & palabra, double negatividad);

    virtual void aumentarNeutralidad(const std::string & palabra, double neutralidad);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:

    // valoracion
    std::unordered_map<std::string, sentimiento> sentimiento_por_palabra;
};

};
};
};