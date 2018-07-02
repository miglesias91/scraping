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

    //analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = this->getResultadoFuerzaEnNoticia();
    //if(nullptr != resultado_fuerza_en_noticia)
    //{
    //    resultado_fuerza_en_noticia->armarJson();
    //    this->getJson()->agregarAtributoJson("fuerza_en_noticia", resultado_fuerza_en_noticia->getJson());
    //}

    //analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento = this->getResultadoSentimiento();
    //if (nullptr != resultado_sentimiento)
    //{
    //    std::vector<std::pair<std::string, float>> fuerzas = resultado_fuerza_en_noticia->getTop(100);

    //    std::vector<std::string> terminos_a_filtrar;
    //    std::for_each(fuerzas.begin(), fuerzas.end(), [&terminos_a_filtrar](std::pair<std::string, float> termino_fuerza) {
    //        terminos_a_filtrar.push_back(termino_fuerza.first);
    //    });

    //    resultado_sentimiento->filtrar(terminos_a_filtrar);

    //    resultado_sentimiento->armarJson();
    //    this->getJson()->agregarAtributoJson("sentimiento", resultado_sentimiento->getJson());
    //}

    return true;
}

bool ResultadoAnalisisContenido::parsearJson()
{
    this->ResultadoAnalisis::parsearJson();

    this->categoria_contenido = this->getJson()->getAtributoValorString("categoria");
    this->fecha_resultado = herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(this->getJson()->getAtributoValorString("fecha"));

    //herramientas::utiles::Json * json_fuerza_en_noticia = nullptr;
    //if(this->getJson()->contieneAtributo("fuerza_en_noticia"))
    //{
    //    analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = this->getResultadoFuerzaEnNoticia();
    //    json_fuerza_en_noticia = this->getJson()->getAtributoValorJson("fuerza_en_noticia");
    //    resultado_fuerza_en_noticia->setJson(json_fuerza_en_noticia);
    //    resultado_fuerza_en_noticia->parsearJson();
    //}

    //herramientas::utiles::Json * json_sentimiento = nullptr;
    //if (this->getJson()->contieneAtributo("sentimiento"))
    //{
    //    analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento = this->getResultadoSentimiento();
    //    json_sentimiento = this->getJson()->getAtributoValorJson("sentimiento");
    //    resultado_sentimiento->setJson(json_sentimiento);
    //    resultado_sentimiento->parsearJson();
    //}

    return true;
}

// CONSULTAS
