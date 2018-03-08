#include <extraccion/include/Medio.h>

// stl
#include <algorithm>

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

std::unordered_map<std::string, std::vector<unsigned long long int>> Medio::getMapaIDsContenidosAnalizados()
{
    return this->mapa_ids_contenidos_analizados;
}

std::unordered_map<std::string, std::vector<unsigned long long int>> Medio::getMapaIDsContenidosNoAnalizados()
{
    return this->mapa_ids_contenidos_no_analizados;
}

std::unordered_map<std::string, std::vector<unsigned long long int>> Medio::getMapaIDsContenidosHistoricos()
{
    return this->mapa_ids_contenidos_historicos;
}

std::vector<std::pair<std::string, std::vector<unsigned long long int>>> Medio::getParesIDsContenidosAnalizados()
{
    return std::vector<std::pair<std::string, std::vector<unsigned long long int>>>(this->mapa_ids_contenidos_analizados.begin(), this->mapa_ids_contenidos_analizados.end());
}

std::vector<std::pair<std::string, std::vector<unsigned long long int>>> Medio::getParesIDsContenidosNoAnalizados()
{
    return std::vector<std::pair<std::string, std::vector<unsigned long long int>>>(this->mapa_ids_contenidos_analizados.begin(), this->mapa_ids_contenidos_no_analizados.end());
}

// GETTERS

std::vector<unsigned long long int> Medio::getIDsContenidosAnalizados()
{
    std::vector<unsigned long long int> ids_contenidos_analizados;

    for (std::unordered_map<std::string, std::vector<unsigned long long int>>::iterator it = this->mapa_ids_contenidos_analizados.begin(); it != this->mapa_ids_contenidos_analizados.end(); it++)
    {
        ids_contenidos_analizados.insert(ids_contenidos_analizados.end(), it->second.begin(), it->second.end());
    }

    return ids_contenidos_analizados;
}

std::vector<unsigned long long int> Medio::getIDsContenidosNoAnalizados()
{
    std::vector<unsigned long long int> ids_contenidos_no_analizados;

    for (std::unordered_map<std::string, std::vector<unsigned long long int>>::iterator it = this->mapa_ids_contenidos_no_analizados.begin(); it != this->mapa_ids_contenidos_no_analizados.end(); it++)
    {
        ids_contenidos_no_analizados.insert(ids_contenidos_no_analizados.end(), it->second.begin(), it->second.end());
    }

    return ids_contenidos_no_analizados;
}

herramientas::utiles::Fecha Medio::getFechaContenidoHistoricoMasReciente()
{
    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    if (vector_mapa_ids_contenidos_historicos.empty())
    {
        return herramientas::utiles::Fecha(0, 0, 0);
    }

    std::sort(vector_mapa_ids_contenidos_historicos.begin(), vector_mapa_ids_contenidos_historicos.end());

    return herramientas::utiles::Fecha::parsearFormatoAAAAMMDD((vector_mapa_ids_contenidos_historicos.end() - 1)->first);
}

herramientas::utiles::Fecha Medio::getFechaContenidoHistoricoMasAntiguo()
{
    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    if (vector_mapa_ids_contenidos_historicos.empty())
    {
        return herramientas::utiles::Fecha(0, 0, 0);
    }

    std::sort(vector_mapa_ids_contenidos_historicos.begin(), vector_mapa_ids_contenidos_historicos.end());

    return herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(vector_mapa_ids_contenidos_historicos.begin()->first);
}

unsigned long long int Medio::getCantidadDeContenidosHistoricos()
{
    if (this->mapa_ids_contenidos_historicos.empty())
    {
        return 0;
    }

    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    unsigned long long int cantidad_de_contenidos_historicos = 0;
    for (std::vector<std::pair<std::string, std::vector<unsigned long long int>>>::iterator it = vector_mapa_ids_contenidos_historicos.begin(); it != vector_mapa_ids_contenidos_historicos.end(); it++)
    {
        cantidad_de_contenidos_historicos += it->second.size();
    }

    return cantidad_de_contenidos_historicos;
}

std::string Medio::getValorAlmacenable()
{
    this->armarJson();

    herramientas::utiles::Json json_almacenable;

    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> vector_mapa_ids_contenidos_no_analizados(this->mapa_ids_contenidos_no_analizados.begin(), this->mapa_ids_contenidos_no_analizados.end());
    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> vector_mapa_ids_contenidos_analizados(this->mapa_ids_contenidos_analizados.begin(), this->mapa_ids_contenidos_analizados.end());
    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_no_analizados;
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_analizados;
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_historicos;

    for (std::vector<std::pair<std::string, std::vector<unsigned long long int>>>::iterator it = vector_mapa_ids_contenidos_no_analizados.begin(); it != vector_mapa_ids_contenidos_no_analizados.end(); it++)
    {
        std::string fecha = it->first;
        std::vector<unsigned long long int> ids = it->second;

        herramientas::utiles::Json * json_ids_contenidos_no_analizados = new herramientas::utiles::Json();

        json_ids_contenidos_no_analizados->agregarAtributoValor("fecha", fecha);
        json_ids_contenidos_no_analizados->agregarAtributoArray("ids", ids);

        json_mapa_ids_contenidos_no_analizados.push_back(json_ids_contenidos_no_analizados);
    }

    for (std::vector<std::pair<std::string, std::vector<unsigned long long int>>>::iterator it = vector_mapa_ids_contenidos_analizados.begin(); it != vector_mapa_ids_contenidos_analizados.end(); it++)
    {
        std::string fecha = it->first;
        std::vector<unsigned long long int> ids = it->second;

        herramientas::utiles::Json * json_ids_contenidos_analizados = new herramientas::utiles::Json();

        json_ids_contenidos_analizados->agregarAtributoValor("fecha", fecha);
        json_ids_contenidos_analizados->agregarAtributoArray("ids", ids);

        json_mapa_ids_contenidos_analizados.push_back(json_ids_contenidos_analizados);
    }

    for (std::vector<std::pair<std::string, std::vector<unsigned long long int>>>::iterator it = vector_mapa_ids_contenidos_historicos.begin(); it != vector_mapa_ids_contenidos_historicos.end(); it++)
    {
        std::string fecha = it->first;
        std::vector<unsigned long long int> ids = it->second;

        herramientas::utiles::Json * json_ids_contenidos_historicos = new herramientas::utiles::Json();

        json_ids_contenidos_historicos->agregarAtributoValor("fecha", fecha);
        json_ids_contenidos_historicos->agregarAtributoArray("ids", ids);

        json_mapa_ids_contenidos_historicos.push_back(json_ids_contenidos_historicos);
    }

    json_almacenable.agregarAtributoArray("mapa_ids_contenidos_no_analizados", json_mapa_ids_contenidos_no_analizados);
    json_almacenable.agregarAtributoArray("mapa_ids_contenidos_analizados", json_mapa_ids_contenidos_analizados);
    json_almacenable.agregarAtributoArray("mapa_ids_contenidos_historicos", json_mapa_ids_contenidos_historicos);

    // seteo la info del medio.
    herramientas::utiles::Json* json_info_medio = this->getJson();
    json_almacenable.agregarAtributoJson("info_medio", json_info_medio);

    std::string string_almacenable = json_almacenable.jsonString();

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_analizados.begin(); it != json_mapa_ids_contenidos_analizados.end(); it++)
    {
        delete *it;
    }

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_no_analizados.begin(); it != json_mapa_ids_contenidos_no_analizados.end(); it++)
    {
        delete *it;
    }

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_historicos.begin(); it != json_mapa_ids_contenidos_historicos.end(); it++)
    {
        delete *it;
    }

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

void Medio::setMapaIDsContenidosAnalizados(std::unordered_map<std::string, std::vector<unsigned long long int>> mapa)
{
    this->mapa_ids_contenidos_analizados = mapa;
}

void Medio::setMapaIDsContenidosNoAnalizados(std::unordered_map<std::string, std::vector<unsigned long long int>> mapa)
{
    this->mapa_ids_contenidos_no_analizados = mapa;
}

void Medio::setMapaIDsContenidosHistoricos(std::unordered_map<std::string, std::vector<unsigned long long int>> mapa)
{
    this->mapa_ids_contenidos_historicos = mapa;
}

bool Medio::setearContenidoComoAnalizado(Contenido * contenido)
{
    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();

    std::vector<unsigned long long int> * ids_contenidos_no_analizados = &this->mapa_ids_contenidos_no_analizados[string_fecha];

    std::vector<unsigned long long int>::iterator it_a_mover = std::find(ids_contenidos_no_analizados->begin(), ids_contenidos_no_analizados->end(), contenido->getId()->numero());

    if (ids_contenidos_no_analizados->end() == it_a_mover)
    {
        return false;
    }

    std::vector<unsigned long long int> * ids_contenidos_analizados = &this->mapa_ids_contenidos_analizados[string_fecha];
    ids_contenidos_analizados->push_back(*it_a_mover);

    ids_contenidos_no_analizados->erase(it_a_mover);

    if (0 == ids_contenidos_no_analizados->size())
    {
        this->mapa_ids_contenidos_no_analizados.erase(string_fecha);
    }

    return true;
}

bool Medio::setearContenidoComoHistorico(Contenido * contenido)
{
    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();

    std::vector<unsigned long long int> * ids_contenidos_analizados = &this->mapa_ids_contenidos_analizados[string_fecha];

    std::vector<unsigned long long int>::iterator it_a_mover = std::find(ids_contenidos_analizados->begin(), ids_contenidos_analizados->end(), contenido->getId()->numero());

    if (ids_contenidos_analizados->end() == it_a_mover)
    {
        return false;
    }

    std::vector<unsigned long long int> * ids_contenidos_historicos = &this->mapa_ids_contenidos_historicos[string_fecha];
    ids_contenidos_historicos->push_back(*it_a_mover);

    ids_contenidos_analizados->erase(it_a_mover);

    if (0 == ids_contenidos_analizados->size())
    {
        this->mapa_ids_contenidos_analizados.erase(string_fecha);
    }

    return true;
}

// METODOS

void Medio::agregarContenidoParaAnalizar(Contenido * contenido)
{
    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();

    std::vector<unsigned long long int> * ids_contenidos_no_analizados = &this->mapa_ids_contenidos_no_analizados[string_fecha];

    ids_contenidos_no_analizados->push_back(contenido->getId()->numero());
}

// metodos de IAlmacenable

void Medio::asignarNuevoId()
{
    this->setId(gestor_ids_medios.nuevoID());
}

void Medio::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json json_almacenable(valor_almacenable);

    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_no_analizados = json_almacenable.getAtributoArrayJson("mapa_ids_contenidos_no_analizados");
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_analizados = json_almacenable.getAtributoArrayJson("mapa_ids_contenidos_analizados");
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_historicos = json_almacenable.getAtributoArrayJson("mapa_ids_contenidos_historicos");

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_no_analizados.begin(); it != json_mapa_ids_contenidos_no_analizados.end(); it++)
    {
        std::string fecha = (*it)->getAtributoValorString("fecha");
        std::vector<unsigned long long int> ids = (*it)->getAtributoArrayUint("ids");

        this->mapa_ids_contenidos_no_analizados[fecha] = ids;
    }

    for(std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_analizados.begin(); it != json_mapa_ids_contenidos_analizados.end(); it++)
    {
        std::string fecha = (*it)->getAtributoValorString("fecha");
        std::vector<unsigned long long int> ids = (*it)->getAtributoArrayUint("ids");

        this->mapa_ids_contenidos_analizados[fecha] = ids;
    }

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_historicos.begin(); it != json_mapa_ids_contenidos_historicos.end(); it++)
    {
        std::string fecha = (*it)->getAtributoValorString("fecha");
        std::vector<unsigned long long int> ids = (*it)->getAtributoArrayUint("ids");

        this->mapa_ids_contenidos_historicos[fecha] = ids;
    }

    // parseo contenido
    herramientas::utiles::Json* json_info_medio = json_almacenable.getAtributoValorJson("info_medio");

    this->setJson(json_info_medio);
    this->parsearJson();

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_no_analizados.begin(); it != json_mapa_ids_contenidos_no_analizados.end(); it++)
    {
        delete *it;
    }
    
    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_analizados.begin(); it != json_mapa_ids_contenidos_analizados.end(); it++)
    {
        delete *it;
    }

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_historicos.begin(); it != json_mapa_ids_contenidos_historicos.end(); it++)
    {
        delete *it;
    }
}

std::string Medio::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoMedio();
}