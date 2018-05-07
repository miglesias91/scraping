#include <analisis/include/ResultadoSentimiento.h>

// stl
#include <algorithm>
#include <iomanip>
#include <sstream>

// herramientas
#include <utiles/include/FuncionesString.h>

using namespace scraping::analisis::tecnicas;

ResultadoSentimiento::ResultadoSentimiento()
{
}

ResultadoSentimiento::~ResultadoSentimiento()
{
}

ResultadoSentimiento::valoracion ResultadoSentimiento::positividad(const std::string & palabra)
{
    return this->sentimiento_por_palabra[palabra].positividad;
}

ResultadoSentimiento::valoracion ResultadoSentimiento::negatividad(const std::string & palabra)
{
    return this->sentimiento_por_palabra[palabra].negatividad;
}

ResultadoSentimiento::valoracion ResultadoSentimiento::neutralidad(const std::string & palabra)
{
    return this->sentimiento_por_palabra[palabra].neutralidad;
}

// GETTERS

// SETTERS

// METODOS

std::unordered_map<std::string, ResultadoSentimiento::sentimiento> scraping::analisis::tecnicas::ResultadoSentimiento::sentimientos()
{
    return this->sentimiento_por_palabra;
}

void ResultadoSentimiento::sumar(const std::string & palabra, const sentimiento & sentimiento)
{
    auto it_valoracion = this->sentimiento_por_palabra.find(palabra);

    if (this->sentimiento_por_palabra.count(palabra))
    {
        (&this->sentimiento_por_palabra[palabra])->positividad += sentimiento.positividad;
        (&this->sentimiento_por_palabra[palabra])->negatividad += sentimiento.negatividad;
        (&this->sentimiento_por_palabra[palabra])->neutralidad += sentimiento.neutralidad;
    }
    else
    {
        this->sentimiento_por_palabra[palabra] = sentimiento;
    }
}

void ResultadoSentimiento::sumar(ResultadoSentimiento * resultado_a_sumar)
{
    auto sentimientos = resultado_a_sumar->sentimientos();

    std::for_each(sentimientos.begin(), sentimientos.end(),
        [this](std::pair<std::string, sentimiento> palabra_sentimiento)
    {
        this->sumar(palabra_sentimiento.first, palabra_sentimiento.second);
    });
}

void ResultadoSentimiento::aumentarPositividad(const std::string & palabra, double positividad)
{
    if (this->sentimiento_por_palabra.count(palabra))
    {
        (&this->sentimiento_por_palabra[palabra])->positividad.suma += positividad;
    }
    else
    {
        sentimiento sentimiento_nuevo = { valoracion{ positividad, 1 } , valoracion{ 0, 0 } , valoracion{ 0, 0 } };
        this->sentimiento_por_palabra[palabra] = sentimiento_nuevo;
    }
}

void ResultadoSentimiento::aumentarNegatividad(const std::string & palabra, double negatividad)
{
    if (this->sentimiento_por_palabra.count(palabra))
    {
        (&this->sentimiento_por_palabra[palabra])->negatividad.suma += negatividad;
    }
    else
    {
        sentimiento sentimiento_nuevo = { valoracion{ 0, 0 }, valoracion{ negatividad, 1 } , valoracion{ 0, 0 } };
        this->sentimiento_por_palabra[palabra] = sentimiento_nuevo;
    }
}

void ResultadoSentimiento::aumentarNeutralidad(const std::string & palabra, double neutralidad)
{
    if (this->sentimiento_por_palabra.count(palabra))
    {
        (&this->sentimiento_por_palabra[palabra])->neutralidad.suma += neutralidad;
    }
    else
    {
        sentimiento sentimiento_nuevo = { valoracion{ 0, 0 }, valoracion{ 0, 0 }, valoracion{ neutralidad, 1 } };
        this->sentimiento_por_palabra[palabra] = sentimiento_nuevo;
    }
}

// metodos de IContieneJson

bool ResultadoSentimiento::armarJson()
{
    this->getJson()->reset();

    std::vector<std::string> sentimiento_por_palabra;
    std::for_each(this->sentimiento_por_palabra.begin(), this->sentimiento_por_palabra.end(),
        [&sentimiento_por_palabra](std::pair<std::string, sentimiento> palabra_sentimiento)
    {
        std::string sentimiento_escrito = palabra_sentimiento.second.escribir();

        sentimiento_por_palabra.push_back(palabra_sentimiento.first + "_" + sentimiento_escrito);
    });

    herramientas::utiles::Json * json = this->getJson();
    json->agregarAtributoArray("valores", sentimiento_por_palabra);

    return true;
}

bool ResultadoSentimiento::parsearJson()
{
    std::vector<std::string> json_sentimientos = this->getJson()->getAtributoArrayString("valores");

    std::for_each(json_sentimientos.begin(), json_sentimientos.end(),
        [this](std::string palabra_sentimiento_escritos)
    {
        std::vector<std::string> palabra_sentimiento_escrito = herramientas::utiles::FuncionesString::separar(palabra_sentimiento_escritos, "_");

        sentimiento sentimiento;
        sentimiento.leer(palabra_sentimiento_escrito[1]);

        this->sentimiento_por_palabra[palabra_sentimiento_escrito[0]] = sentimiento;
    });

    return true;
}

// CONSULTAS