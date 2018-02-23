#include <twitter/include/Cuenta.h>

using namespace scraping::twitter::modelo;

// scraping
#include <scraping/include/ConfiguracionScraping.h>

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

std::string Cuenta::getGrupoMedio()
{
    return scraping::ConfiguracionScraping::prefijoTwitter();
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

// metodos de Medio

scraping::extraccion::Medio * Cuenta::clonar()
{
    Cuenta * clon = new Cuenta(this->getNombre());
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());

    clon->setIdUltimoTweetAnalizado(this->getIdUltimoTweetAnalizado());

    clon->setMapaIDsContenidosAnalizados(this->getMapaIDsContenidosAnalizados());
    clon->setMapaIDsContenidosNoAnalizados(this->getMapaIDsContenidosNoAnalizados());
    clon->setMapaIDsContenidosHistoricos(this->getMapaIDsContenidosHistoricos());

    return clon;
}

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

// metodos de IHashable

unsigned long long int Cuenta::hashcode()
{
    return herramientas::utiles::IHashable::hashear(this->getNombre());
}

// CONSULTAS