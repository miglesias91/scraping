#include <preparacion/include/ResultadoAnalisisDiario.h>

// stl
#include <algorithm>

// herramientas
#include <utiles/include/Fecha.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::preparacion;

ResultadoAnalisisDiario::ResultadoAnalisisDiario()
    : IAlmacenable(ConfiguracionScraping::prefijoResultadoDiario()), IContieneJson()
{
}

ResultadoAnalisisDiario::~ResultadoAnalisisDiario()
{
    std::vector<std::pair<unsigned long long int, ResultadoAnalisisMedio*>> vector_resultados_medios(this->resultados_medios.begin(), this->resultados_medios.end());

    for (std::vector<std::pair<unsigned long long int, ResultadoAnalisisMedio*>>::iterator it = vector_resultados_medios.begin(); it != vector_resultados_medios.end(); it++)
    {
        if (nullptr != it->second)
        {
            delete it->second;
            it->second = nullptr;
        }
    }
    this->resultados_medios.clear();
}

// GETTERS

herramientas::utiles::Json * ResultadoAnalisisDiario::getRegistroAExportar()
{
    return nullptr;
}

ResultadoAnalisisMedio * ResultadoAnalisisDiario::getResultadoMedio(unsigned long long int id_medio) const {
    if (false == this->existeResultadoDeMedio(id_medio))
    {
        return nullptr;
    }

    return this->resultados_medios.at(id_medio);
}

herramientas::utiles::ID ResultadoAnalisisDiario::getIDDiario()
{
    std::string id_string = herramientas::utiles::Fecha::getFechaActual().getStringAAAAMMDD();

    unsigned long long int id = std::stoull(id_string);

    return herramientas::utiles::ID(id);
}

// getters de IAlmacenable

std::string ResultadoAnalisisDiario::getValorAlmacenable()
{
    this->armarJson();

    return this->getJson()->jsonString();
}

// SETTERS

// METODOS

void ResultadoAnalisisDiario::filtrar(const std::vector<unsigned long long int> & ids_medios_a_filtrar, const std::vector<std::string> & terminos_a_filtrar)
{
    for (auto it = this->resultados_medios.begin(); it != this->resultados_medios.end(); )
    {
        if (std::count(ids_medios_a_filtrar.cbegin(), ids_medios_a_filtrar.cend(), it->first))
        {
            it->second->filtrar(terminos_a_filtrar);
            it++;
        }
        else
        {
            delete it->second;
            it = this->resultados_medios.erase(it);
        }
    }
}

void ResultadoAnalisisDiario::agregarResultadoDeMedio(ResultadoAnalisisMedio * resultado_medio)
{
    unsigned long long int id_medio = resultado_medio->getId()->numero();

    std::unordered_map<unsigned long long int, ResultadoAnalisisMedio*>::iterator it_medio = this->resultados_medios.find(id_medio);

    if (this->resultados_medios.end() == it_medio)
    {// si no existe, entonces agrego uno nuevo.
        this->resultados_medios[id_medio] = new ResultadoAnalisisMedio();
    }

    this->resultados_medios[id_medio]->combinarCon(resultado_medio);
}

// metodos de IContieneJson

bool ResultadoAnalisisDiario::armarJson()
{
    this->getJson()->reset();

    std::vector<herramientas::utiles::Json*> json_medios;

    std::vector<std::pair<unsigned long long int, ResultadoAnalisisMedio*>> vector_resultados_medios(this->resultados_medios.begin(), this->resultados_medios.end());

    for (std::vector<std::pair<unsigned long long int, ResultadoAnalisisMedio*>>::iterator it = vector_resultados_medios.begin(); it != vector_resultados_medios.end(); it++)
    {
        unsigned long long int id_medio = it->first;

        it->second->armarJson();
        herramientas::utiles::Json * json_analisis = it->second->getJson();

        herramientas::utiles::Json * json_medio = new herramientas::utiles::Json();

        json_medio->agregarAtributoValor("id_medio", id_medio);
        json_medio->agregarAtributoJson("analisis", json_analisis);

        json_medios.push_back(json_medio);
    }

    this->getJson()->agregarAtributoArray("analisis_medios", json_medios);

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_medios.begin(); it != json_medios.end(); it++)
    {// los elimino xq "agregarAtributoArray" crea una copia.
        delete (*it);
    }

    return true;
}

bool ResultadoAnalisisDiario::parsearJson()
{
    std::vector<herramientas::utiles::Json*> json_medios = this->getJson()->getAtributoArrayJson("analisis_medios");

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_medios.begin(); it != json_medios.end(); it++)
    {
        unsigned long long int id_medio = (*it)->getAtributoValorUint("id_medio");
        herramientas::utiles::Json * json_analisis = (*it)->getAtributoValorJson("analisis");

        ResultadoAnalisisMedio * resultado_analisis_medio = new ResultadoAnalisisMedio();
        resultado_analisis_medio->setId(new herramientas::utiles::ID(id_medio));

        resultado_analisis_medio->setJson(json_analisis);
        resultado_analisis_medio->parsearJson();

        this->agregarResultadoDeMedio(resultado_analisis_medio);

        delete resultado_analisis_medio;
    }

    for (std::vector<herramientas::utiles::Json*>::iterator it = json_medios.begin(); it != json_medios.end(); it++)
    {
        delete *it;
    }
    json_medios.clear();

    return true;
}

// metodos de IAlmacenable

void ResultadoAnalisisDiario::asignarNuevoId()
{

}

void ResultadoAnalisisDiario::parsearValorAlmacenable(std::string valor_almacenable)
{
    herramientas::utiles::Json * json_almacenable = new herramientas::utiles::Json(valor_almacenable);

    this->setJson(json_almacenable);

    bool parseo_correcto = this->parsearJson();
}

std::string ResultadoAnalisisDiario::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultadoDiario();
}

// CONSULTAS

bool ResultadoAnalisisDiario::existeResultadoDeMedio(unsigned long long int id_medio) const
{
    if (this->resultados_medios.end() == this->resultados_medios.find(id_medio))
    {
        return false;
    }

    return true;
}