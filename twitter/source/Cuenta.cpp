#include <twitter/include/Cuenta.h>

using namespace scraping::twitter::modelo;

Cuenta::Cuenta(std::string nombre) : Medio(), nombre(nombre), id_ultimo_tweet_analizado(0)
{
}

Cuenta::~Cuenta()
{
}

// GETTERS

std::string Cuenta::getNombre()
{
    return this->nombre;
}

unsigned long long int Cuenta::getIdUltimoTweetAnalizado()
{
    return this->id_ultimo_tweet_analizado;
}

// metodos de IAlmacenable

std::string Cuenta::getValorAlmacenable()
{
    this->armarJson();

    herramientas::utiles::Json* json_info_contenido = this->getJson();

    std::string string_almacenable = json_info_contenido->jsonString();

    return string_almacenable;
}

// SETTERS

void Cuenta::setNombre(std::string nombre)
{
    this->nombre = nombre;
}

void Cuenta::setIdUltimoTweetAnalizado(unsigned long long int id_ultimo_tweet_analizado)
{
    this->id_ultimo_tweet_analizado = id_ultimo_tweet_analizado;
}

// METODOS

// metodos de IContieneJson

bool Cuenta::armarJson()
{
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("nombre_cuenta", this->getNombre());

    this->getJson()->agregarAtributoValor("id_ultimo_tweet_analizado", this->getIdUltimoTweetAnalizado());

    return true;
}

bool Cuenta::parsearJson()
{
    std::string nombre_cuenta = this->getJson()->getAtributoValorString("nombre_cuenta");

    unsigned long long int id_ultimo_tweet_analizado = this->getJson()->getAtributoValorUint("id_ultimo_tweet_analizado");

    this->setNombre(nombre_cuenta);

    this->setIdUltimoTweetAnalizado(id_ultimo_tweet_analizado);

    return true;
}

// metodos de IAlmacenable

void Cuenta::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json * json_almacenable = new herramientas::utiles::Json(valor_almacenable);

    this->setJson(json_almacenable);
    this->parsearJson();
}

// metodos de IHashable

unsigned long long int Cuenta::hashcode()
{
    return herramientas::utiles::IHashable::hashear(this->getNombre());
}

// CONSULTAS