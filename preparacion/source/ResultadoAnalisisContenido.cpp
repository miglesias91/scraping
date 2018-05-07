#include <preparacion/include/ResultadoAnalisisContenido.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

using namespace scraping::preparacion;

ResultadoAnalisisContenido::ResultadoAnalisisContenido(
    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia,
    scraping::analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento
)
    : ResultadoAnalisis(ConfiguracionScraping::prefijoResultadoContenido(), resultado_fuerza_en_noticia, resultado_sentimiento)
{
}

ResultadoAnalisisContenido::~ResultadoAnalisisContenido()
{
}

// GETTERS

// SETTERS

// METODOS

// metodos de IAlmacenable

std::string ResultadoAnalisisContenido::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultadoContenido();
}

// CONSULTAS
