#include <preparacion/include/ResultadoAnalisisContenido.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

// analisis
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoSentimiento.h>

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

herramientas::utiles::Fecha ResultadoAnalisisContenido::fecha() const {
    return this->fecha_resultado;
}

std::string ResultadoAnalisisContenido::categoria() const {
    return this->categoria_contenido;
}


// SETTERS

void ResultadoAnalisisContenido::fecha(const herramientas::utiles::Fecha & fecha_resultado) {
    this->fecha_resultado = fecha_resultado;
}

void ResultadoAnalisisContenido::categoria(const std::string & categoria_contenido) {
    this->categoria_contenido = categoria_contenido;
}

// METODOS

// metodos de IAlmacenable

std::string ResultadoAnalisisContenido::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultadoContenido();
}

// metodos de IContieneJson

bool ResultadoAnalisisContenido::armarJson()
{
    this->ResultadoAnalisis::armarJson();

    this->getJson()->agregarAtributoValor("fecha", this->fecha_resultado.getStringAAAAMMDDHHmmSS());
    this->getJson()->agregarAtributoValor("categoria", this->categoria_contenido);

    return true;
}

bool ResultadoAnalisisContenido::parsearJson()
{
    this->ResultadoAnalisis::parsearJson();

    this->categoria_contenido = this->getJson()->getAtributoValorString("categoria");
    this->fecha_resultado = herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(this->getJson()->getAtributoValorString("fecha"));

    return true;
}

// CONSULTAS
