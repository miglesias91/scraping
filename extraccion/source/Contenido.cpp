#include <extraccion/include/Contenido.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion;

herramientas::utiles::GestorIDs Contenido::gestor_ids_contenidos;

Contenido::Contenido(herramientas::utiles::Json * json) : IAlmacenable(ConfiguracionScraping::prefijoContenido()), IContieneJson(json)
{
}

Contenido::~Contenido()
{
}
// GETTERS

std::string Contenido::getTexto()
{
    return this->texto;
}

std::string Contenido::getClaveIDActual()
{
    return ConfiguracionScraping::claveIDContenidoActual();
}

herramientas::utiles::GestorIDs * scraping::extraccion::Contenido::getGestorIDs()
{
    return &gestor_ids_contenidos;
}

// getters de IAlmacenable
std::string Contenido::getValorAlmacenable()
{
    this->armarJson();

    herramientas::utiles::Json json_almacenable;

    // agrego el texto.
    // json_almacenable.agregarAtributoValor("texto_contenido", this->getTexto());

    // seteo la info del medio.
    herramientas::utiles::Json* json_info_contenido = this->getJson();
    json_almacenable.agregarAtributoJson("info_contenido", json_info_contenido);

    std::string string_almacenable = json_almacenable.jsonString();

    return string_almacenable;
}

// SETTERS

void Contenido::setTexto(std::string texto)
{
    this->texto = texto;
}

// METODOS

// metodos de IAlmacenable

void Contenido::asignarNuevoId()
{
    this->setId(gestor_ids_contenidos.nuevoID());
}

void Contenido::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json json_almacenable(valor_almacenable);

    // parseo los ids no analizados.
    // this->texto = json_almacenable.getAtributoValorString("texto_contenido");

    // parseo contenido
    herramientas::utiles::Json* json_info_contenido = json_almacenable.getAtributoValorJson("info_contenido");

    this->setJson(json_info_contenido);
    this->parsearJson();
}

std::string Contenido::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoContenido();
}