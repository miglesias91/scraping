#include <extraccion/include/Medio.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion;

herramientas::utiles::GestorIDs Medio::gestor_ids_medios;

Medio::Medio() : IAlmacenable(ConfiguracionScraping::prefijoMedio())
{
}

Medio::~Medio()
{
}

// GETTERS

std::vector<unsigned long long int> Medio::getIDsContenidosAnalizados()
{
    return this->ids_contenidos_analizados;
}

std::vector<unsigned long long int> Medio::getIDsContenidosNoAnalizados()
{
    return this->ids_contenidos_no_analizados;
}

std::string Medio::getValorAlmacenable()
{
    return std::string();
}

std::string Medio::getClaveIDActual()
{
    return ConfiguracionScraping::claveIDMedioActual();
}

herramientas::utiles::GestorIDs * Medio::getGestorIDs()
{
    return &gestor_ids_medios;
}

// SETTERS

// METODOS

void Medio::agregarContenidoParaAnalizar(Contenido * contenido)
{
    this->ids_contenidos_no_analizados.push_back(contenido->getId()->numero());
}

// metodos de IAlmacenable

void Medio::asignarNuevoId()
{
    this->setId(gestor_ids_medios.nuevoID());
}

void Medio::parsearValorAlmacenable(std::string valor_almacenable)
{

}

std::string Medio::prefijoGrupo()
{
    return std::string();
}