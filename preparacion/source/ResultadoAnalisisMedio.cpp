#include <preparacion/include/ResultadoAnalisisMedio.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::preparacion;

ResultadoAnalisisMedio::ResultadoAnalisisMedio(scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia)
    : ResultadoAnalisis(ConfiguracionScraping::prefijoResultadoMedio(), resultado_fuerza_en_noticia)
{
}

ResultadoAnalisisMedio::~ResultadoAnalisisMedio()
{
}

// GETTERS

// SETTERS

// METODOS

// metodos de IAlmacenable

std::string ResultadoAnalisisMedio::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultadoMedio();
}

// CONSULTAS
