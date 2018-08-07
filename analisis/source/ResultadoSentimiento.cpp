#include <analisis/include/ResultadoSentimiento.h>

// stl
#include <algorithm>
#include <iomanip>
#include <sstream>

// herramientas
#include <utiles/include/FuncionesString.h>

using namespace scraping::analisis::tecnicas;

ResultadoSentimiento::ResultadoSentimiento(const uint32_t & maximo_valores_a_almacenar) : maximo_valores_a_almacenar(maximo_valores_a_almacenar)
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

std::unordered_map<std::string, ResultadoSentimiento::sentimiento> ResultadoSentimiento::sentimientos()
{
    return this->sentimiento_por_palabra;
}

ResultadoSentimiento::sentimiento ResultadoSentimiento::valores(const std::string expresion) const
{
    if ('*' == *(expresion.end() - 1)) {
        std::string comienzo_de_palabra(expresion.begin(), expresion.end() - 1);
        return this->sentimiento_comodin(comienzo_de_palabra);
    }

    if (false == this->existePalabra(expresion))
    {
        return sentimiento();
    }

    return this->sentimiento_por_palabra.at(expresion);
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
        (&this->sentimiento_por_palabra[palabra])->positividad += positividad;
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
        (&this->sentimiento_por_palabra[palabra])->negatividad += negatividad;
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
        (&this->sentimiento_por_palabra[palabra])->neutralidad += neutralidad;
    }
    else
    {
        sentimiento sentimiento_nuevo = { valoracion{ 0, 0 }, valoracion{ 0, 0 }, valoracion{ neutralidad, 1 } };
        this->sentimiento_por_palabra[palabra] = sentimiento_nuevo;
    }
}

bool ResultadoSentimiento::top(std::vector<std::pair<std::string, sentimiento>>* sentimientos_top, const uint32_t & top_max) {
    *sentimientos_top = std::vector<std::pair<std::string, sentimiento>>(this->sentimiento_por_palabra.begin(), this->sentimiento_por_palabra.end());

    std::sort(sentimientos_top->begin(), sentimientos_top->end(),
        [](std::pair<std::string, sentimiento> a, std::pair<std::string, sentimiento> b) {
        return a.second.total() > b.second.total();
    });

    if (sentimientos_top->size() > top_max) {
        sentimientos_top->resize(top_max);
    }

    return true;
}

// metodos de IResultadoTecnica

void ResultadoSentimiento::filtrar(const std::vector<std::string> & terminos_a_filtrar)
{
    for (auto it = this->sentimiento_por_palabra.begin(); it != this->sentimiento_por_palabra.end(); )
    {
        std::string palabra = it->first;
        if (std::count_if(terminos_a_filtrar.cbegin(), terminos_a_filtrar.cend(), [this, &palabra](std::string termino_a_filtrar)
        {
            return this->match(palabra, termino_a_filtrar);
        }))
        {
            it++;
        }
        else
        {
            it = this->sentimiento_por_palabra.erase(it);
        }
    }
}

// metodos de IContieneJson

bool ResultadoSentimiento::armarJson()
{
    this->getJson()->reset();

    std::vector<std::pair<std::string, sentimiento>> sentimientos_top;
    this->top(&sentimientos_top, this->maximo_valores_a_almacenar);

    std::vector<std::string> sentimiento_por_palabra;
    std::for_each(sentimientos_top.begin(), sentimientos_top.end(),
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

bool ResultadoSentimiento::existePalabra(const std::string &palabra) const
{
    if (this->sentimiento_por_palabra.end() == this->sentimiento_por_palabra.find(palabra))
    {
        return false;
    }

    return true;
}

ResultadoSentimiento::sentimiento ResultadoSentimiento::sentimiento_comodin(const std::string & comodin) const
{
    sentimiento sentimiento_total;
    std::for_each(this->sentimiento_por_palabra.begin(), this->sentimiento_por_palabra.end(),
        [&comodin, &sentimiento_total](std::pair<std::string, sentimiento> sentimiento_palabra)
    {
        if (herramientas::utiles::FuncionesString::empiezaCon(sentimiento_palabra.first, comodin)) {
            sentimiento_total += sentimiento_palabra.second;
        }
    });

    return sentimiento_total;
}
