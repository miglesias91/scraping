#include <preparacion/include/ResultadoAnalisisDiario.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::preparacion;

ResultadoAnalisisDiario::ResultadoAnalisisDiario()
    : IAlmacenable(ConfiguracionScraping::prefijoResultadoDiario()), IContieneJson()
{
}

ResultadoAnalisisDiario::~ResultadoAnalisisDiario()
{
}


// GETTERS

// getters de IAlmacenable

std::string ResultadoAnalisisDiario::getValorAlmacenable()
{

}

// SETTERS

// METODOS

void ResultadoAnalisisDiario::agregarMedio(ResultadoAnalisisMedio * resultado_medio)
{
    this->resultados_medios.push_back(resultado_medio);
}

// metodos de IContieneJson

bool ResultadoAnalisisDiario::armarJson()
{
    this->getJson()->reset();

    for (std::vector<ResultadoAnalisisMedio*>::iterator it = this->resultados_medios.begin(); it != this->resultados_medios.end(); it++)
    {
        std::string id_medio = (*it)->getId()->string();
        herramientas::utiles::Json * json = (*it)->getJson();

        this->getJson()->agregarAtributoJson(id_medio, json);
    }

    return true;
}

bool ResultadoAnalisisDiario::parsearJson()
{

}

// metodos de IAlmacenable

void ResultadoAnalisisDiario::asignarNuevoId()
{

}

void ResultadoAnalisisDiario::parsearValorAlmacenable(std::string valor_almacenable)
{

}

std::string ResultadoAnalisisDiario::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultadoDiario();
}

// CONSULTAS
