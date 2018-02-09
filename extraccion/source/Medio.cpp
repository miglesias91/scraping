#include <extraccion/include/Medio.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion;

herramientas::utiles::GestorIDs Medio::gestor_ids_medios;

Medio::Medio(herramientas::utiles::Json * json) : IAlmacenable(ConfiguracionScraping::prefijoMedio()), IContieneJson(json), IHashable()
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
    this->armarJson();

    herramientas::utiles::Json json_almacenable;

    // agrego las ids no analizados.
    json_almacenable.agregarAtributoArray("ids_contenidos_no_analizados", this->getIDsContenidosNoAnalizados());

    // agrego las ids no analizados.
    json_almacenable.agregarAtributoArray("ids_contenidos_analizados", this->getIDsContenidosAnalizados());

    // seteo la info del medio.
    herramientas::utiles::Json* json_info_medio = this->getJson();
    json_almacenable.agregarAtributoJson("info_medio", json_info_medio);

    std::string string_almacenable = json_almacenable.jsonString();

    return string_almacenable;
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

bool Medio::setearContenidoComoAnalizado(Contenido * contenido)
{
    std::vector<unsigned long long int>::iterator it_a_mover = std::find(this->ids_contenidos_no_analizados.begin(), this->ids_contenidos_no_analizados.end(), contenido->getId()->numero());

    if (this->ids_contenidos_no_analizados.end() == it_a_mover)
    {
        return false;
    }

    this->ids_contenidos_analizados.push_back(*it_a_mover);

    this->ids_contenidos_no_analizados.erase(it_a_mover);

    return false;
}

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
    herramientas::utiles::Json json_almacenable(valor_almacenable);

    // parseo los ids no analizados.
    this->ids_contenidos_no_analizados = json_almacenable.getAtributoArrayUint("ids_contenidos_no_analizados");

    // parseo los ids analizados.
    this->ids_contenidos_no_analizados = json_almacenable.getAtributoArrayUint("ids_contenidos_no_analizados");

    // parseo contenido
    herramientas::utiles::Json* json_info_medio = json_almacenable.getAtributoValorJson("info_medio");

    this->setJson(json_info_medio);
    this->parsearJson();

    // delete json_info_medio;
}

std::string Medio::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoMedio();
}