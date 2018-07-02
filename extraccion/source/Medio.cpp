#include <extraccion/include/Medio.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::extraccion;

herramientas::utiles::GestorIDs Medio::gestor_ids_medios;

Medio::Medio(const std::string & prefijo_grupo, herramientas::utiles::Json * json)
    : prefijo_grupo(prefijo_grupo), IAlmacenable(prefijo_grupo), IContieneJson(json), IHashable() {}

Medio::~Medio() {}

bool Medio::ids_para_depurar(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa) {
    *mapa = this->mapa_ids_contenidos_para_depurar;

    return true;
}

bool Medio::ids_para_depurar(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares) {
    *pares = std::vector<std::pair<std::string, std::vector<uintmax_t>>>(this->mapa_ids_contenidos_para_depurar.begin(), this->mapa_ids_contenidos_para_depurar.end());

    return true;
}

bool Medio::ids_para_depurar(std::vector<uintmax_t> * vector) {

    std::for_each(this->mapa_ids_contenidos_para_depurar.begin(), this->mapa_ids_contenidos_para_depurar.end(),
        [&vector](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {
        vector->insert(vector->end(), fecha_ids.second.begin(), fecha_ids.second.end());
    });

    return true;
}

bool Medio::ids_para_analizar(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa) {
    *mapa = this->mapa_ids_contenidos_para_analizar;

    return true;
}

bool Medio::ids_para_analizar(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares) {
    *pares = std::vector<std::pair<std::string, std::vector<uintmax_t>>>(this->mapa_ids_contenidos_para_analizar.begin(), this->mapa_ids_contenidos_para_analizar.end());

    return true;
}

bool Medio::ids_para_analizar(std::vector<uintmax_t> * vector) {

    std::for_each(this->mapa_ids_contenidos_para_analizar.begin(), this->mapa_ids_contenidos_para_analizar.end(),
        [&vector](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {
        vector->insert(vector->end(), fecha_ids.second.begin(), fecha_ids.second.end());
    });

    return true;
}

bool Medio::ids_para_preparar(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa) {
    *mapa = this->mapa_ids_contenidos_para_preparar;

    return true;
}
bool Medio::ids_para_preparar(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares) {
    *pares = std::vector<std::pair<std::string, std::vector<uintmax_t>>>(this->mapa_ids_contenidos_para_preparar.begin(), this->mapa_ids_contenidos_para_preparar.end());

    return true;
}
bool Medio::ids_para_preparar(std::vector<uintmax_t> * vector) {

    std::for_each(this->mapa_ids_contenidos_para_preparar.begin(), this->mapa_ids_contenidos_para_preparar.end(),
        [&vector](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {
        vector->insert(vector->end(), fecha_ids.second.begin(), fecha_ids.second.end());
    });

    return true;
}

bool Medio::ids_historicos(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa) {
    *mapa = this->mapa_ids_contenidos_historicos;

    return true;
}
bool Medio::ids_historicos(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares) {
    *pares = std::vector<std::pair<std::string, std::vector<uintmax_t>>>(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    return true;
}
bool Medio::ids_historicos(std::vector<uintmax_t> * vector) {
    std::for_each(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end(),
        [&vector](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {
        vector->insert(vector->end(), fecha_ids.second.begin(), fecha_ids.second.end());
    });

    return true;
}
//
//std::unordered_map<std::string, std::vector<uintmax_t>> Medio::getMapaIDsContenidosParaDepurar()
//{
//    return this->mapa_ids_contenidos_analizados;
//}
//
//std::unordered_map<std::string, std::vector<uintmax_t>> Medio::getMapaIDsContenidosParaDepurar()
//{
//    return this->mapa_ids_contenidos_analizados;
//}
//
//std::unordered_map<std::string, std::vector<uintmax_t>> Medio::getMapaIDsContenidosParaAnalizar()
//{
//    return this->mapa_ids_contenidos_no_analizados;
//}
//
//std::unordered_map<std::string, std::vector<uintmax_t>> Medio::getMapaIDsContenidosHistoricos()
//{
//    return this->mapa_ids_contenidos_historicos;
//}
//
//std::vector<std::pair<std::string, std::vector<uintmax_t>>> Medio::getParesIDsContenidosAnalizados()
//{
//    return std::vector<std::pair<std::string, std::vector<uintmax_t>>>(this->mapa_ids_contenidos_analizados.begin(), this->mapa_ids_contenidos_analizados.end());
//}
//
//std::vector<std::pair<std::string, std::vector<uintmax_t>>> Medio::getParesIDsContenidosNoAnalizados()
//{
//    return std::vector<std::pair<std::string, std::vector<uintmax_t>>>(this->mapa_ids_contenidos_analizados.begin(), this->mapa_ids_contenidos_no_analizados.end());
//}
//
// GETTERS
//
//std::vector<uintmax_t> Medio::getIDsContenidosAnalizados()
//{
//    std::vector<uintmax_t> ids_contenidos_analizados;
//
//    for (std::unordered_map<std::string, std::vector<uintmax_t>>::iterator it = this->mapa_ids_contenidos_analizados.begin(); it != this->mapa_ids_contenidos_analizados.end(); it++)
//    {
//        ids_contenidos_analizados.insert(ids_contenidos_analizados.end(), it->second.begin(), it->second.end());
//    }
//
//    return ids_contenidos_analizados;
//}
//
//std::vector<uintmax_t> Medio::getIDsContenidosNoAnalizados()
//{
//    std::vector<uintmax_t> ids_contenidos_no_analizados;
//
//    for (std::unordered_map<std::string, std::vector<uintmax_t>>::iterator it = this->mapa_ids_contenidos_no_analizados.begin(); it != this->mapa_ids_contenidos_no_analizados.end(); it++)
//    {
//        ids_contenidos_no_analizados.insert(ids_contenidos_no_analizados.end(), it->second.begin(), it->second.end());
//    }
//
//    return ids_contenidos_no_analizados;
//}

herramientas::utiles::Fecha Medio::getFechaContenidoHistoricoMasReciente()
{
    std::vector<std::pair<std::string, std::vector<uintmax_t>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    if (vector_mapa_ids_contenidos_historicos.empty())
    {
        return herramientas::utiles::Fecha(0, 0, 0);
    }

    std::sort(vector_mapa_ids_contenidos_historicos.begin(), vector_mapa_ids_contenidos_historicos.end());

    return herramientas::utiles::Fecha::parsearFormatoAAAAMMDD((vector_mapa_ids_contenidos_historicos.end() - 1)->first);
}

herramientas::utiles::Fecha Medio::getFechaContenidoHistoricoMasAntiguo()
{
    std::vector<std::pair<std::string, std::vector<uintmax_t>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    if (vector_mapa_ids_contenidos_historicos.empty())
    {
        return herramientas::utiles::Fecha(0, 0, 0);
    }

    std::sort(vector_mapa_ids_contenidos_historicos.begin(), vector_mapa_ids_contenidos_historicos.end());

    return herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(vector_mapa_ids_contenidos_historicos.begin()->first);
}

uintmax_t Medio::getCantidadDeContenidosHistoricos()
{
    if (this->mapa_ids_contenidos_historicos.empty())
    {
        return 0;
    }

    std::vector<std::pair<std::string, std::vector<uintmax_t>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    uintmax_t cantidad_de_contenidos_historicos = 0;
    for (std::vector<std::pair<std::string, std::vector<uintmax_t>>>::iterator it = vector_mapa_ids_contenidos_historicos.begin(); it != vector_mapa_ids_contenidos_historicos.end(); it++)
    {
        cantidad_de_contenidos_historicos += it->second.size();
    }

    return cantidad_de_contenidos_historicos;
}

std::string Medio::getValorAlmacenable()
{
    this->armarJson();

    herramientas::utiles::Json json_almacenable;

    std::vector<std::pair<std::string, std::vector<uintmax_t>>> vector_mapa_ids_contenidos_para_depurar(this->mapa_ids_contenidos_para_depurar.begin(), this->mapa_ids_contenidos_para_depurar.end());
    std::vector<std::pair<std::string, std::vector<uintmax_t>>> vector_mapa_ids_contenidos_para_analizar(this->mapa_ids_contenidos_para_analizar.begin(), this->mapa_ids_contenidos_para_analizar.end());
    std::vector<std::pair<std::string, std::vector<uintmax_t>>> vector_mapa_ids_contenidos_para_preparar(this->mapa_ids_contenidos_para_preparar.begin(), this->mapa_ids_contenidos_para_preparar.end());
    std::vector<std::pair<std::string, std::vector<uintmax_t>>> vector_mapa_ids_contenidos_historicos(this->mapa_ids_contenidos_historicos.begin(), this->mapa_ids_contenidos_historicos.end());

    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_para_depurar;
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_para_analizar;
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_para_preparar;
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_historicos;

    std::for_each(vector_mapa_ids_contenidos_para_depurar.begin(), vector_mapa_ids_contenidos_para_depurar.end(),
        [&json_mapa_ids_contenidos_para_depurar](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {

        herramientas::utiles::Json * json_ids_contenidos_para_depurar = new herramientas::utiles::Json();

        json_ids_contenidos_para_depurar->agregarAtributoValor("fecha", fecha_ids.first);
        json_ids_contenidos_para_depurar->agregarAtributoArray("ids", fecha_ids.second);

        json_mapa_ids_contenidos_para_depurar.push_back(json_ids_contenidos_para_depurar);
    });

    std::for_each(vector_mapa_ids_contenidos_para_analizar.begin(), vector_mapa_ids_contenidos_para_analizar.end(),
        [&json_mapa_ids_contenidos_para_analizar](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {

        herramientas::utiles::Json * json_ids_contenidos_para_analizar = new herramientas::utiles::Json();

        json_ids_contenidos_para_analizar->agregarAtributoValor("fecha", fecha_ids.first);
        json_ids_contenidos_para_analizar->agregarAtributoArray("ids", fecha_ids.second);

        json_mapa_ids_contenidos_para_analizar.push_back(json_ids_contenidos_para_analizar);
    });

    std::for_each(vector_mapa_ids_contenidos_para_preparar.begin(), vector_mapa_ids_contenidos_para_preparar.end(),
        [&json_mapa_ids_contenidos_para_preparar](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {

        herramientas::utiles::Json * json_ids_contenidos_para_preparar = new herramientas::utiles::Json();

        json_ids_contenidos_para_preparar->agregarAtributoValor("fecha", fecha_ids.first);
        json_ids_contenidos_para_preparar->agregarAtributoArray("ids", fecha_ids.second);

        json_mapa_ids_contenidos_para_preparar.push_back(json_ids_contenidos_para_preparar);
    });

    std::for_each(vector_mapa_ids_contenidos_historicos.begin(), vector_mapa_ids_contenidos_historicos.end(),
        [&json_mapa_ids_contenidos_historicos](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {

        herramientas::utiles::Json * json_ids_contenidos_historicos = new herramientas::utiles::Json();

        json_ids_contenidos_historicos->agregarAtributoValor("fecha", fecha_ids.first);
        json_ids_contenidos_historicos->agregarAtributoArray("ids", fecha_ids.second);

        json_mapa_ids_contenidos_historicos.push_back(json_ids_contenidos_historicos);
    });

    //for (std::vector<std::pair<std::string, std::vector<uintmax_t>>>::iterator it = vector_mapa_ids_contenidos_no_analizados.begin(); it != vector_mapa_ids_contenidos_no_analizados.end(); it++)
    //{
    //    std::string fecha = it->first;
    //    std::vector<uintmax_t> ids = it->second;

    //    herramientas::utiles::Json * json_ids_contenidos_no_analizados = new herramientas::utiles::Json();

    //    json_ids_contenidos_no_analizados->agregarAtributoValor("fecha", fecha);
    //    json_ids_contenidos_no_analizados->agregarAtributoArray("ids", ids);

    //    json_mapa_ids_contenidos_no_analizados.push_back(json_ids_contenidos_no_analizados);
    //}

    //for (std::vector<std::pair<std::string, std::vector<uintmax_t>>>::iterator it = vector_mapa_ids_contenidos_analizados.begin(); it != vector_mapa_ids_contenidos_analizados.end(); it++)
    //{
    //    std::string fecha = it->first;
    //    std::vector<uintmax_t> ids = it->second;

    //    herramientas::utiles::Json * json_ids_contenidos_analizados = new herramientas::utiles::Json();

    //    json_ids_contenidos_analizados->agregarAtributoValor("fecha", fecha);
    //    json_ids_contenidos_analizados->agregarAtributoArray("ids", ids);

    //    json_mapa_ids_contenidos_analizados.push_back(json_ids_contenidos_analizados);
    //}

    //for (std::vector<std::pair<std::string, std::vector<uintmax_t>>>::iterator it = vector_mapa_ids_contenidos_historicos.begin(); it != vector_mapa_ids_contenidos_historicos.end(); it++)
    //{
    //    std::string fecha = it->first;
    //    std::vector<uintmax_t> ids = it->second;

    //    herramientas::utiles::Json * json_ids_contenidos_historicos = new herramientas::utiles::Json();

    //    json_ids_contenidos_historicos->agregarAtributoValor("fecha", fecha);
    //    json_ids_contenidos_historicos->agregarAtributoArray("ids", ids);

    //    json_mapa_ids_contenidos_historicos.push_back(json_ids_contenidos_historicos);
    //}

    json_almacenable.agregarAtributoArray("mapa_ids_contenidos_para_depurar", json_mapa_ids_contenidos_para_depurar);
    json_almacenable.agregarAtributoArray("mapa_ids_contenidos_para_analizar", json_mapa_ids_contenidos_para_analizar);
    json_almacenable.agregarAtributoArray("mapa_ids_contenidos_para_preparar", json_mapa_ids_contenidos_para_preparar);
    json_almacenable.agregarAtributoArray("mapa_ids_contenidos_historicos", json_mapa_ids_contenidos_historicos);

    // seteo la info del medio.
    herramientas::utiles::Json* json_info_medio = this->getJson();
    json_almacenable.agregarAtributoJson("info_medio", json_info_medio);

    std::string string_almacenable = json_almacenable.jsonString();

    std::for_each(json_mapa_ids_contenidos_para_depurar.begin(), json_mapa_ids_contenidos_para_depurar.end(), [](herramientas::utiles::Json* json) { delete json; });
    std::for_each(json_mapa_ids_contenidos_para_analizar.begin(), json_mapa_ids_contenidos_para_analizar.end(), [](herramientas::utiles::Json* json) { delete json; });
    std::for_each(json_mapa_ids_contenidos_para_preparar.begin(), json_mapa_ids_contenidos_para_preparar.end(), [](herramientas::utiles::Json* json) { delete json; });
    std::for_each(json_mapa_ids_contenidos_historicos.begin(), json_mapa_ids_contenidos_historicos.end(), [](herramientas::utiles::Json* json) { delete json; });

    return string_almacenable;
}

void Medio::set_ids_para_depurar(const std::unordered_map<std::string, std::vector<uintmax_t>>& mapa) {
    this->mapa_ids_contenidos_para_depurar = mapa;
}

void Medio::set_ids_para_analizar(const std::unordered_map<std::string, std::vector<uintmax_t>>& mapa) {
    this->mapa_ids_contenidos_para_analizar = mapa;
}

void Medio::set_ids_para_preparar(const std::unordered_map<std::string, std::vector<uintmax_t>>& mapa) {
    this->mapa_ids_contenidos_para_preparar = mapa;
}

void Medio::set_ids_historicos(const std::unordered_map<std::string, std::vector<uintmax_t>>& mapa) {
    this->mapa_ids_contenidos_historicos = mapa;
}

bool Medio::contenido_depurado(Contenido * contenido) {
    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();

    std::vector<uintmax_t> * ids_contenidos_para_depurar = &this->mapa_ids_contenidos_para_depurar[string_fecha];

    std::vector<uintmax_t>::iterator it_a_mover = std::find(ids_contenidos_para_depurar->begin(), ids_contenidos_para_depurar->end(), contenido->getId()->numero());
    if (ids_contenidos_para_depurar->end() == it_a_mover) {
        return false;
    }

    std::vector<uintmax_t> * ids_contenidos_para_analizar = &this->mapa_ids_contenidos_para_analizar[string_fecha];
    ids_contenidos_para_analizar->push_back(*it_a_mover);

    ids_contenidos_para_depurar->erase(it_a_mover);

    if (0 == ids_contenidos_para_depurar->size()) {
        this->mapa_ids_contenidos_para_depurar.erase(string_fecha);
    }

    return true;
}

bool Medio::contenido_analizado(Contenido * contenido) {
    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();

    std::vector<uintmax_t> * ids_contenidos_para_analizar = &this->mapa_ids_contenidos_para_analizar[string_fecha];

    std::vector<uintmax_t>::iterator it_a_mover = std::find(ids_contenidos_para_analizar->begin(), ids_contenidos_para_analizar->end(), contenido->getId()->numero());
    if (ids_contenidos_para_analizar->end() == it_a_mover) {
        return false;
    }

    std::vector<uintmax_t> * ids_contenidos_para_preparar = &this->mapa_ids_contenidos_para_preparar[string_fecha];
    ids_contenidos_para_preparar->push_back(*it_a_mover);

    ids_contenidos_para_analizar->erase(it_a_mover);

    if (0 == ids_contenidos_para_analizar->size()) {
        this->mapa_ids_contenidos_para_analizar.erase(string_fecha);
    }

    return true;
}

bool Medio::contenido_preparado(Contenido * contenido) {
    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();

    std::vector<uintmax_t> * ids_contenidos_para_preparar = &this->mapa_ids_contenidos_para_preparar[string_fecha];

    std::vector<uintmax_t>::iterator it_a_mover = std::find(ids_contenidos_para_preparar->begin(), ids_contenidos_para_preparar->end(), contenido->getId()->numero());
    if (ids_contenidos_para_preparar->end() == it_a_mover) {
        return false;
    }

    std::vector<uintmax_t> * ids_contenidos_historicos = &this->mapa_ids_contenidos_historicos[string_fecha];
    ids_contenidos_historicos->push_back(*it_a_mover);

    ids_contenidos_para_preparar->erase(it_a_mover);

    if (0 == ids_contenidos_para_preparar->size()) {
        this->mapa_ids_contenidos_para_preparar.erase(string_fecha);
    }

    return true;
}

bool Medio::contenido_depurado(const std::string & fecha_aaaammdd, const uintmax_t & id_contenido) {
    Contenido contenido("", "", "", herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(fecha_aaaammdd));
    contenido.setId(new herramientas::utiles::ID(id_contenido));

    return this->contenido_depurado(&contenido);
}

bool Medio::contenido_analizado(const std::string & fecha_aaaammdd, const uintmax_t & id_contenido) {
    Contenido contenido("", "", "", herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(fecha_aaaammdd));
    contenido.setId(new herramientas::utiles::ID(id_contenido));

    return this->contenido_analizado(&contenido);
}

bool Medio::contenido_preparado(const std::string & fecha_aaaammdd, const uintmax_t & id_contenido) {
    Contenido contenido("", "", "", herramientas::utiles::Fecha::parsearFormatoAAAAMMDD(fecha_aaaammdd));
    contenido.setId(new herramientas::utiles::ID(id_contenido));

    return this->contenido_preparado(&contenido);
}

bool Medio::contenidos_preparados(const std::string & fecha_aaaammdd, const std::vector<uintmax_t> & ids_contenidos) {

    std::for_each(ids_contenidos.begin(), ids_contenidos.end(), [=](uintmax_t id) {
        if (false == this->contenido_preparado(fecha_aaaammdd, id)) {
            return false;
        }
    });
    return true;
}

std::string Medio::getClaveIDActual() {
    return ConfiguracionScraping::claveIDMedioActual();
}

herramientas::utiles::GestorIDs * Medio::getGestorIDs() {
    return &gestor_ids_medios;
}

// SETTERS

//void Medio::setMapaIDsContenidosAnalizados(std::unordered_map<std::string, std::vector<uintmax_t>> mapa)
//{
//    this->mapa_ids_contenidos_analizados = mapa;
//}
//
//void Medio::setMapaIDsContenidosNoAnalizados(std::unordered_map<std::string, std::vector<uintmax_t>> mapa)
//{
//    this->mapa_ids_contenidos_no_analizados = mapa;
//}
//
//void Medio::setMapaIDsContenidosHistoricos(std::unordered_map<std::string, std::vector<uintmax_t>> mapa)
//{
//    this->mapa_ids_contenidos_historicos = mapa;
//}

//bool Medio::setearContenidoComoAnalizado(Contenido * contenido)
//{
//    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();
//
//    std::vector<uintmax_t> * ids_contenidos_no_analizados = &this->mapa_ids_contenidos_no_analizados[string_fecha];
//
//    std::vector<uintmax_t>::iterator it_a_mover = std::find(ids_contenidos_no_analizados->begin(), ids_contenidos_no_analizados->end(), contenido->getId()->numero());
//
//    if (ids_contenidos_no_analizados->end() == it_a_mover)
//    {
//        return false;
//    }
//
//    std::vector<uintmax_t> * ids_contenidos_analizados = &this->mapa_ids_contenidos_analizados[string_fecha];
//    ids_contenidos_analizados->push_back(*it_a_mover);
//
//    ids_contenidos_no_analizados->erase(it_a_mover);
//
//    if (0 == ids_contenidos_no_analizados->size())
//    {
//        this->mapa_ids_contenidos_no_analizados.erase(string_fecha);
//    }
//
//    return true;
//}
//
//bool Medio::setearContenidoComoHistorico(Contenido * contenido)
//{
//    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();
//
//    std::vector<uintmax_t> * ids_contenidos_analizados = &this->mapa_ids_contenidos_analizados[string_fecha];
//
//    std::vector<uintmax_t>::iterator it_a_mover = std::find(ids_contenidos_analizados->begin(), ids_contenidos_analizados->end(), contenido->getId()->numero());
//
//    if (ids_contenidos_analizados->end() == it_a_mover)
//    {
//        return false;
//    }
//
//    std::vector<uintmax_t> * ids_contenidos_historicos = &this->mapa_ids_contenidos_historicos[string_fecha];
//    ids_contenidos_historicos->push_back(*it_a_mover);
//
//    ids_contenidos_analizados->erase(it_a_mover);
//
//    if (0 == ids_contenidos_analizados->size())
//    {
//        this->mapa_ids_contenidos_analizados.erase(string_fecha);
//    }
//
//    return true;
//}

// METODOS

void Medio::nuevo(Contenido * contenido) {
    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();

    std::vector<uintmax_t> * ids_contenidos_no_analizados = &this->mapa_ids_contenidos_para_depurar[string_fecha];

    ids_contenidos_no_analizados->push_back(contenido->getId()->numero());
}

//void Medio::agregarContenidoParaAnalizar(Contenido * contenido)
//{
//    std::string string_fecha = contenido->getFecha().getStringAAAAMMDD();
//
//    std::vector<uintmax_t> * ids_contenidos_no_analizados = &this->mapa_ids_contenidos_no_analizados[string_fecha];
//
//    ids_contenidos_no_analizados->push_back(contenido->getId()->numero());
//}

// metodos de IAlmacenable

void Medio::asignarNuevoId()
{
    this->setId(gestor_ids_medios.nuevoID());
}

void Medio::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json json_almacenable(valor_almacenable);

    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_para_depurar = json_almacenable.getAtributoArrayJson("mapa_ids_contenidos_para_depurar");
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_para_analizar = json_almacenable.getAtributoArrayJson("mapa_ids_contenidos_para_analizar");
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_para_preparar = json_almacenable.getAtributoArrayJson("mapa_ids_contenidos_para_preparar");
    std::vector<herramientas::utiles::Json*> json_mapa_ids_contenidos_historicos = json_almacenable.getAtributoArrayJson("mapa_ids_contenidos_historicos");

    std::for_each(json_mapa_ids_contenidos_para_depurar.begin(), json_mapa_ids_contenidos_para_depurar.end(),
        [this](herramientas::utiles::Json * json_contenidos_por_fecha) {

        std::string fecha = json_contenidos_por_fecha->getAtributoValorString("fecha");
        std::vector<uintmax_t> ids = json_contenidos_por_fecha->getAtributoArrayUint("ids");

        this->mapa_ids_contenidos_para_depurar[fecha] = ids;
    });

    std::for_each(json_mapa_ids_contenidos_para_analizar.begin(), json_mapa_ids_contenidos_para_analizar.end(),
        [this](herramientas::utiles::Json * json_contenidos_por_fecha) {

        std::string fecha = json_contenidos_por_fecha->getAtributoValorString("fecha");
        std::vector<uintmax_t> ids = json_contenidos_por_fecha->getAtributoArrayUint("ids");

        this->mapa_ids_contenidos_para_analizar[fecha] = ids;
    });

    std::for_each(json_mapa_ids_contenidos_para_preparar.begin(), json_mapa_ids_contenidos_para_preparar.end(),
        [this](herramientas::utiles::Json * json_contenidos_por_fecha) {

        std::string fecha = json_contenidos_por_fecha->getAtributoValorString("fecha");
        std::vector<uintmax_t> ids = json_contenidos_por_fecha->getAtributoArrayUint("ids");

        this->mapa_ids_contenidos_para_preparar[fecha] = ids;
    });

    std::for_each(json_mapa_ids_contenidos_historicos.begin(), json_mapa_ids_contenidos_historicos.end(),
        [this](herramientas::utiles::Json * json_contenidos_por_fecha) {

        std::string fecha = json_contenidos_por_fecha->getAtributoValorString("fecha");
        std::vector<uintmax_t> ids = json_contenidos_por_fecha->getAtributoArrayUint("ids");

        this->mapa_ids_contenidos_historicos[fecha] = ids;
    });

    // parseo contenido
    herramientas::utiles::Json* json_info_medio = json_almacenable.getAtributoValorJson("info_medio");

    this->setJson(json_info_medio);
    this->parsearJson();

    std::for_each(json_mapa_ids_contenidos_para_depurar.begin(), json_mapa_ids_contenidos_para_depurar.end(), [](herramientas::utiles::Json * json) { delete json; });
    std::for_each(json_mapa_ids_contenidos_para_analizar.begin(), json_mapa_ids_contenidos_para_analizar.end(), [](herramientas::utiles::Json * json) { delete json; });
    std::for_each(json_mapa_ids_contenidos_para_preparar.begin(), json_mapa_ids_contenidos_para_preparar.end(), [](herramientas::utiles::Json * json) { delete json; });
    std::for_each(json_mapa_ids_contenidos_historicos.begin(), json_mapa_ids_contenidos_historicos.end(), [](herramientas::utiles::Json * json) { delete json; });

    //for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_no_analizados.begin(); it != json_mapa_ids_contenidos_no_analizados.end(); it++)
    //{
    //    std::string fecha = (*it)->getAtributoValorString("fecha");
    //    std::vector<uintmax_t> ids = (*it)->getAtributoArrayUint("ids");

    //    this->mapa_ids_contenidos_no_analizados[fecha] = ids;
    //}

    //for(std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_analizados.begin(); it != json_mapa_ids_contenidos_analizados.end(); it++)
    //{
    //    std::string fecha = (*it)->getAtributoValorString("fecha");
    //    std::vector<uintmax_t> ids = (*it)->getAtributoArrayUint("ids");

    //    this->mapa_ids_contenidos_analizados[fecha] = ids;
    //}

    //for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_historicos.begin(); it != json_mapa_ids_contenidos_historicos.end(); it++)
    //{
    //    std::string fecha = (*it)->getAtributoValorString("fecha");
    //    std::vector<uintmax_t> ids = (*it)->getAtributoArrayUint("ids");

    //    this->mapa_ids_contenidos_historicos[fecha] = ids;
    //}



    //for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_no_analizados.begin(); it != json_mapa_ids_contenidos_no_analizados.end(); it++)
    //{
    //    delete *it;
    //}
    //
    //for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_analizados.begin(); it != json_mapa_ids_contenidos_analizados.end(); it++)
    //{
    //    delete *it;
    //}

    //for (std::vector<herramientas::utiles::Json*>::iterator it = json_mapa_ids_contenidos_historicos.begin(); it != json_mapa_ids_contenidos_historicos.end(); it++)
    //{
    //    delete *it;
    //}
}

std::string Medio::prefijoGrupo() {
    return this->prefijo_grupo;
    //return ConfiguracionScraping::prefijoMedio();
}