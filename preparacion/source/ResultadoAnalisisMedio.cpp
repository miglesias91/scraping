#include <preparacion/include/ResultadoAnalisisMedio.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

// analisis
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoSentimiento.h>

using namespace scraping::preparacion;

ResultadoAnalisisMedio::ResultadoAnalisisMedio(
    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia,
    scraping::analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento
)
    : ResultadoAnalisis(ConfiguracionScraping::prefijoResultadoMedio(), resultado_fuerza_en_noticia, resultado_sentimiento) {}

ResultadoAnalisisMedio::~ResultadoAnalisisMedio() {
    std::for_each(this->resultados.begin(), this->resultados.end(),
    [=](std::pair<std::string, ResultadoAnalisisContenido*> categoria_resultado) {
        delete categoria_resultado.second;
    });
}

void ResultadoAnalisisMedio::resultados_por_categoria(std::unordered_map<std::string, ResultadoAnalisisContenido*>* resultados) {
    *resultados = this->resultados;
}

// GETTERS

// SETTERS

void ResultadoAnalisisMedio::set_resultado_de_categoria(const std::string & categoria, ResultadoAnalisisContenido * resultado) {
    this->resultados[categoria] = resultado;
}

// METODOS

// metodos de IAlmacenable

// metodos de ResultadoAnalisis
void ResultadoAnalisisMedio::combinarCon(ResultadoAnalisisMedio * resultado_a_combinar) {
    std::unordered_map<std::string, ResultadoAnalisisContenido*> resultados_por_categ;
    resultado_a_combinar->resultados_por_categoria(&resultados_por_categ);

    std::for_each(resultados_por_categ.begin(), resultados_por_categ.end(),
        [=](std::pair<std::string, ResultadoAnalisisContenido*> categoria_resultado) {
        if (0 == this->resultados.count(categoria_resultado.first)) {
            this->resultados[categoria_resultado.first] = new ResultadoAnalisisContenido();
        }
        this->resultados[categoria_resultado.first]->combinarCon(categoria_resultado.second);
    });

    this->ResultadoAnalisis::combinarCon(resultado_a_combinar);
}

std::string ResultadoAnalisisMedio::prefijoGrupo()
{
    return ConfiguracionScraping::prefijoResultadoMedio();
}

bool ResultadoAnalisisMedio::armarJson() {
    this->getJson()->reset();

    std::vector<herramientas::utiles::Json*> jsons_categorias;
    std::for_each(this->resultados.begin(), this->resultados.end(),
        [=, &jsons_categorias](std::pair<std::string, ResultadoAnalisisContenido*> categoria_resultado) {

        herramientas::utiles::Json * json_categoria = new herramientas::utiles::Json();

        json_categoria->agregarAtributoValor("categoria", categoria_resultado.first);

        analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = categoria_resultado.second->getResultadoFuerzaEnNoticia();
        if(nullptr != resultado_fuerza_en_noticia) {
            resultado_fuerza_en_noticia->armarJson();
            json_categoria->agregarAtributoJson("fuerza_en_noticia", resultado_fuerza_en_noticia->getJson());
        }

        analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento = categoria_resultado.second->getResultadoSentimiento();
        if (nullptr != resultado_sentimiento) {
            std::vector<std::pair<std::string, float>> fuerzas = resultado_fuerza_en_noticia->getTop(100);

            std::vector<std::string> terminos_a_filtrar;
            std::for_each(fuerzas.begin(), fuerzas.end(), [&terminos_a_filtrar](std::pair<std::string, float> termino_fuerza) {
                terminos_a_filtrar.push_back(termino_fuerza.first);
            });

            resultado_sentimiento->filtrar(terminos_a_filtrar);

            resultado_sentimiento->armarJson();
            json_categoria->agregarAtributoJson("sentimiento", resultado_sentimiento->getJson());
        }

        jsons_categorias.push_back(json_categoria);
    });

    this->getJson()->agregarAtributoArray("categorias", jsons_categorias);

    std::for_each(jsons_categorias.begin(), jsons_categorias.end(), [](herramientas::utiles::Json * json) { delete json; });
    return true;
}

// metodos de IContieneJson

bool ResultadoAnalisisMedio::parsearJson() {

    std::vector<herramientas::utiles::Json*> jsons_categorias = this->getJson()->getAtributoArrayJson("categorias");

    std::for_each(jsons_categorias.begin(), jsons_categorias.end(),
        [=](herramientas::utiles::Json * json_categoria) {

        std::string categoria = json_categoria->getAtributoValorString("categoria");

        ResultadoAnalisisContenido * resultado = new ResultadoAnalisisContenido();

        herramientas::utiles::Json * json_fuerza_en_noticia = nullptr;
        analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = resultado->getResultadoFuerzaEnNoticia();
        if(json_categoria->contieneAtributo("fuerza_en_noticia")) {
            json_fuerza_en_noticia = json_categoria->getAtributoValorJson("fuerza_en_noticia");
            resultado_fuerza_en_noticia->setJson(json_fuerza_en_noticia);
            resultado_fuerza_en_noticia->parsearJson();
        }

        herramientas::utiles::Json * json_sentimiento = nullptr;
        analisis::tecnicas::ResultadoSentimiento * resultado_sentimiento = resultado->getResultadoSentimiento();
        if (json_categoria->contieneAtributo("sentimiento")) {
            json_sentimiento = json_categoria->getAtributoValorJson("sentimiento");
            resultado_sentimiento->setJson(json_sentimiento);
            resultado_sentimiento->parsearJson();
        }

        if (this->resultados.count(categoria)){
            delete this->resultados[categoria];
        }
        this->resultados[categoria] = resultado;
    });

    return true;
}

// CONSULTAS
