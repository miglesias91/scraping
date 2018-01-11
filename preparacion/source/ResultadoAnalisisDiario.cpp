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

// SETTERS

// METODOS

void ResultadoAnalisisDiario::agregarMedio(ResultadoAnalisisMedio * resultado_medio)
{
    this->resultados_medios.push_back(resultado_medio);
}

// metodos de IAlmacenable

std::string ResultadoAnalisisDiario::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultadoDiario();
}

// CONSULTAS
