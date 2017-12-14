#include <twitter/include/Tweet.h>

// stl
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

// herramientas
#include <utiles/include/Conversiones.h>

using namespace scraping::twitter::modelo;

Tweet::Tweet(herramientas::utiles::Json * tweet_json) : herramientas::utiles::IContieneJson(tweet_json)
{
    unsigned long long int id = this->getJson()->getAtributoValorUint("id");
    std::string fecha_creacion_formato_twitter = this->getJson()->getAtributoValorString("created_at");
    std::string texto = this->getJson()->getAtributoValorString("text");

    herramientas::utiles::Json * user_json = this->getJson()->getAtributoValorJson("user");
    unsigned long long int id_usuario = user_json->getAtributoValorUint("id");
    delete user_json;

    herramientas::utiles::Json * entidades_json = this->getJson()->getAtributoValorJson("entities");
    std::vector<std::string> hashtags = entidades_json->getAtributoArrayString("hashtags");
    delete entidades_json;

    this->setId(id);
    this->setFechaCreacion(this->parsearFechaEnFormatoTwitter(fecha_creacion_formato_twitter));
    this->setTexto(texto);
    this->setIdUsuario(id_usuario);
    this->setHashtags(hashtags);
}

Tweet::~Tweet()
{
}

// GETTERS

unsigned long long int Tweet::getId()
{
    return this->id;
}

herramientas::utiles::Fecha Tweet::getFechaCreacion()
{
    return this->fecha_creacion;
}

std::string Tweet::getTexto()
{
    return this->texto;
}

unsigned long long int Tweet::getIdUsuario()
{
    return this->id_usuario;
}

std::vector<std::string> Tweet::getHashtags()
{
    return this->hashtags;
}

// SETTERS

void Tweet::setId(unsigned long long int id)
{
    this->id = id;
}

void Tweet::setFechaCreacion(herramientas::utiles::Fecha fecha_creacion)
{
    this->fecha_creacion = fecha_creacion;
}

void Tweet::setTexto(std::string texto)
{
    this->texto = texto;
}

void Tweet::setIdUsuario(unsigned long long int id_usuario)
{
    this->id_usuario = id_usuario;
}

void Tweet::setHashtags(std::vector<std::string> hashtags)
{
    this->hashtags = hashtags;
}

// METODOS

void Tweet::agregarHashtags(std::string hashtag)
{
    this->hashtags.push_back(hashtag);
}

// CONSULTAS

bool Tweet::contieneHashtag(std::string hashtag)
{
    if (this->hashtags.end() == std::find(this->hashtags.begin(), this->hashtags.end(), hashtag))
    {
        return false;
    }
    return true;
}

// OPERADORES

// METODOS PRIVADOS

herramientas::utiles::Fecha Tweet::parsearFechaEnFormatoTwitter(std::string fecha_formato_twitter)
{
    herramientas::utiles::Fecha fecha;
    // la fecha viene en formato "Fri Dec 08 20:33:39 +0000 2017" --> le borro los "+0000 "
    // para que me quede "Fri Dec 08 20:33:39 2017" y la pueda parsear bien.
    size_t posicion_signo_mas = fecha_formato_twitter.find_first_of('+');

    fecha_formato_twitter.erase(posicion_signo_mas, 6);

    std::stringstream stream_fecha(fecha_formato_twitter);

    std::tm t = {};
    stream_fecha >> std::get_time(&t, "%a %b %d %H:%M:%S %Y");

    if (stream_fecha.fail())
    {
        std::cout << "Fecha formato error.\n";
    }
    else
    {
        fecha.setAnio(t.tm_year + 1900);
        fecha.setMes(t.tm_mon + 1);
        fecha.setDia(t.tm_mday);
    }

    return fecha;
}