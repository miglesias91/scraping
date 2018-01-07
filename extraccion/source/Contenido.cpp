#include <extraccion/include/Contenido.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion;

herramientas::utiles::GestorIDs Contenido::gestor_ids_contenidos;

Contenido::Contenido() : IAlmacenable(ConfiguracionScraping::prefijoContenido())
{
}

Contenido::~Contenido()
{
}
// GETTERS

std::string Contenido::getValorAlmacenable()
{
    return std::string();
}

std::string Contenido::getClaveIDActual()
{
    return ConfiguracionScraping::claveIDContenidoActual();
}

herramientas::utiles::GestorIDs * scraping::extraccion::Contenido::getGestorIDs()
{
    return &gestor_ids_contenidos;
}
// SETTERS

// METODOS

// metodos de IAlmacenable

void Contenido::asignarNuevoId()
{
    this->setId(gestor_ids_contenidos.nuevoID());
}

void Contenido::parsearValorAlmacenable(std::string valor_almacenable)
{

}

std::string Contenido::prefijoGrupo()
{
    return std::string();
}