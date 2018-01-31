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
    return 0;
}

// SETTERS

void Cuenta::setNombre(std::string nombre)
{
    this->nombre = nombre;
}

void Cuenta::setIdUltimoTweetAnalizado(unsigned long long int id_ultimo_tweet_analizado)
{
}

// METODOS

// metodos de IContieneJson

bool Cuenta::armarJson()
{
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("nombre_cuenta", this->getNombre());

    this->getJson()->agregarAtributoValor("id_ultimo_tweet_analizado", this->getNombre());

    return true;
}

bool Cuenta::parsearJson()
{
    std::string nombre_cuenta = this->getJson()->getAtributoValorString("nombre_cuenta");

    this->setNombre(nombre_cuenta);

    return true;
}

// CONSULTAS