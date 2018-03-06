#include <facebook/include/Pagina.h>

using namespace scraping::facebook::modelo;

// scraping
#include <scraping/include/ConfiguracionScraping.h>

Pagina::Pagina(std::string nombre) : Medio(), nombre(nombre), fecha_ultima_publicacion_analizada(0,0,0)
{
}

Pagina::~Pagina()
{
}

// GETTERS

std::string Pagina::getNombre()
{
    return this->nombre;
}

herramientas::utiles::Fecha Pagina::getFechaUltimaPublicacionAnalizada()
{
    return this->fecha_ultima_publicacion_analizada;
}

std::string Pagina::getGrupoMedio()
{
    return scraping::ConfiguracionScraping::prefijoTwitter();
}

// SETTERS

void Pagina::setNombre(std::string nombre)
{
    this->nombre = nombre;
}

void Pagina::setFechaUltimaPublicacionAnalizada(herramientas::utiles::Fecha fecha_ultima_publicacion_analizada)
{
    this->fecha_ultima_publicacion_analizada = fecha_ultima_publicacion_analizada;
}

// METODOS

// metodos de Medio

scraping::extraccion::Medio * Pagina::clonar()
{
    Pagina * clon = new Pagina(this->getNombre());
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());

    clon->setFechaUltimaPublicacionAnalizada(this->getFechaUltimaPublicacionAnalizada());

    clon->setMapaIDsContenidosAnalizados(this->getMapaIDsContenidosAnalizados());
    clon->setMapaIDsContenidosNoAnalizados(this->getMapaIDsContenidosNoAnalizados());
    clon->setMapaIDsContenidosHistoricos(this->getMapaIDsContenidosHistoricos());

    return clon;
}

// metodos de IContieneJson

bool Pagina::armarJson()
{
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("nombre_cuenta", this->getNombre());

    this->getJson()->agregarAtributoValor("fecha_ultima_publicacion_analizada", this->getFechaUltimaPublicacionAnalizada().getStringAAAAMMDD());

    return true;
}

bool Pagina::parsearJson()
{
    std::string nombre_cuenta = this->getJson()->getAtributoValorString("nombre_cuenta");

    std::string string_fecha_ultima_publicacion_analizada = this->getJson()->getAtributoValorString("fecha_ultima_publicacion_analizada");

    this->setNombre(nombre_cuenta);

    this->setFechaUltimaPublicacionAnalizada(herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(string_fecha_ultima_publicacion_analizada));

    return true;
}

// metodos de IHashable

unsigned long long int Pagina::hashcode()
{
    return herramientas::utiles::IHashable::hashear(this->getNombre());
}

// CONSULTAS