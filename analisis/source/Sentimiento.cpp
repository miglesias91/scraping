#include <analisis/include/Sentimiento.h>

// stl
#include <algorithm>

// herramientas
#include <utiles/include/Stemming.h>

namespace scraping {
    namespace analisis {
        namespace tecnicas {

std::string Sentimiento::positivo = "P";
std::string Sentimiento::negativo = "N";
std::string Sentimiento::neutral = "NONE";

ia::clasificacion::Vocabulario Sentimiento::vocabulario;
ia::clasificacion::Clasificador Sentimiento::clasificador_tres_clases;
ia::clasificacion::Clasificador Sentimiento::clasificador_dos_clases;

Sentimiento::Sentimiento()
{
}

Sentimiento::~Sentimiento()
{
}

bool Sentimiento::cargar(const configuracion & configuracion_sentimiento)
{
    vocabulario.importar(configuracion_sentimiento.path_vocabulario);

    if (false == clasificador_dos_clases.cargar(configuracion_sentimiento.clasificador_dos_clases.path_red, configuracion_sentimiento.clasificador_dos_clases.path_mapa))
    {
        return false;
    }

    if (clasificador_tres_clases.cargar(configuracion_sentimiento.clasificador_tres_clases.path_red, configuracion_sentimiento.clasificador_tres_clases.path_mapa))
    {
        return false;
    }

    return true;
}

bool Sentimiento::cargar(const std::string & path_configuracion_sentimiento)
{
    std::string contenido_json;
    herramientas::utiles::FuncionesSistemaArchivos::leer(path_configuracion_sentimiento, contenido_json);

    herramientas::utiles::Json json_configuracion(contenido_json);

    vocabulario.importar(json_configuracion.getAtributoValorString("path_vocabulario"));

    std::string path_red;
    std::string path_mapa_clases;

    herramientas::utiles::Json * json_config_clasificador_dos_clases = json_configuracion.getAtributoValorJson("clasificador_dos_clases");
    path_red = json_config_clasificador_dos_clases->getAtributoValorString("path_red");
    path_mapa_clases = json_config_clasificador_dos_clases->getAtributoValorString("path_mapa_clases");
    delete json_config_clasificador_dos_clases;

    if (false == clasificador_dos_clases.cargar(path_red, path_mapa_clases))
    {
        return false;
    }

    herramientas::utiles::Json * json_config_clasificador_tres_clases = json_configuracion.getAtributoValorJson("clasificador_tres_clases");
    path_red = json_config_clasificador_tres_clases->getAtributoValorString("path_red");
    path_mapa_clases = json_config_clasificador_tres_clases->getAtributoValorString("path_mapa_clases");
    delete json_config_clasificador_tres_clases;

    if (false == clasificador_tres_clases.cargar(path_red, path_mapa_clases))
    {
        return false;
    }

    return true;
}

bool scraping::analisis::tecnicas::Sentimiento::liberar()
{
    return true;
}

void Sentimiento::aplicar(const std::vector<std::string> & bolsa_de_palabras, IResultadoTecnica * resultado)
{
    ResultadoSentimiento * resultado_sentimiento = static_cast<ResultadoSentimiento*>(resultado);

    std::vector<uint32_t> atributos_a_predecir;

    {// aplico stemming porque el vocabulario esta basado en palabras "stemmiadas". copio la bolsa de palabras.
        std::vector<std::string> bolsa_de_palabras_stemeadas = bolsa_de_palabras;
        herramientas::utiles::Stemming::stemUTF8(bolsa_de_palabras_stemeadas);

        vocabulario.vectorizar(bolsa_de_palabras_stemeadas, atributos_a_predecir);
    }

    std::vector<float> atributos_float_a_predecir;
    std::for_each(atributos_a_predecir.begin(), atributos_a_predecir.end(), [&atributos_float_a_predecir](uint32_t atributo) { atributos_float_a_predecir.push_back(atributo); });

    std::string prediccion_tres_clases = "";
    clasificador_tres_clases.predecir(atributos_float_a_predecir, prediccion_tres_clases);

    //std::string prediccion_dos_clases = "";
    //clasificador_dos_clases.predecir(atributos_float_a_predecir, prediccion_dos_clases);
    if (prediccion_tres_clases == positivo) {
        this->aumentar_positividad(bolsa_de_palabras, resultado_sentimiento);
        return;
    }

    if (prediccion_tres_clases == negativo) {
        this->aumentar_negatividad(bolsa_de_palabras, resultado_sentimiento);
        return;
    }

    if (prediccion_tres_clases == neutral) {
        this->aumentar_neutralidad(bolsa_de_palabras, resultado_sentimiento);
        return;
    }

    //if (prediccion_tres_clases == neutral && prediccion_dos_clases == negativo)
    //{
    //    std::for_each(bolsa_de_palabras.begin(), bolsa_de_palabras.end(),
    //        [&resultado_sentimiento](std::string palabra)
    //    {
    //        resultado_sentimiento->aumentarNeutralidad(palabra, 1.0f);
    //    });
    //    return;
    //}

    //if (prediccion_tres_clases == negativo && prediccion_dos_clases == positivo)
    //{
    //    std::for_each(bolsa_de_palabras.begin(), bolsa_de_palabras.end(),
    //        [&resultado_sentimiento](std::string palabra)
    //    {
    //        resultado_sentimiento->aumentarNeutralidad(palabra, 1.0f);
    //    });
    //    return;
    //}

    //if (prediccion_tres_clases == positivo && prediccion_dos_clases == negativo)
    //{
    //    std::for_each(bolsa_de_palabras.begin(), bolsa_de_palabras.end(),
    //        [&resultado_sentimiento](std::string palabra)
    //    {
    //        resultado_sentimiento->aumentarNeutralidad(palabra, 1.0f);
    //    });
    //    return;
    //}
}

void Sentimiento::aplicar(scraping::analisis::IAnalizable * contenido_analizable, IResultadoTecnica * resultado)
{
    return this->aplicar(contenido_analizable->getBolsaDePalabras(), resultado);
}

void Sentimiento::aumentar_positividad(const std::vector<std::string>& bolsa_de_palabras, ResultadoSentimiento * resultado_sentimiento) {
    std::vector<std::string>::const_iterator it_segunda_palabra = bolsa_de_palabras.cbegin() + 1;
    std::vector<std::string>::const_iterator it_tercera_palabra = bolsa_de_palabras.cbegin() + 2;
    for (auto palabra : bolsa_de_palabras) {

        resultado_sentimiento->aumentarPositividad(palabra, 1.0f);

        std::string dos_palabras = "";
        if (bolsa_de_palabras.cend() != it_segunda_palabra) {
            dos_palabras = palabra + " " + *it_segunda_palabra;

            resultado_sentimiento->aumentarPositividad(dos_palabras, 1.0f);
            it_segunda_palabra++;
        }

        std::string tres_palabras = "";
        if (bolsa_de_palabras.cend() != it_tercera_palabra) {
            tres_palabras = dos_palabras + " " + *it_tercera_palabra;

            resultado_sentimiento->aumentarPositividad(tres_palabras, 1.0f);
            it_tercera_palabra++;
        }
    }
}

void Sentimiento::aumentar_negatividad(const std::vector<std::string>& bolsa_de_palabras, ResultadoSentimiento * resultado_sentimiento) {
    std::vector<std::string>::const_iterator it_segunda_palabra = bolsa_de_palabras.cbegin() + 1;
    std::vector<std::string>::const_iterator it_tercera_palabra = bolsa_de_palabras.cbegin() + 2;
    for (auto palabra : bolsa_de_palabras) {

        resultado_sentimiento->aumentarNegatividad(palabra, 1.0f);

        std::string dos_palabras = "";
        if (bolsa_de_palabras.cend() != it_segunda_palabra) {
            dos_palabras = palabra + " " + *it_segunda_palabra;

            resultado_sentimiento->aumentarNegatividad(dos_palabras, 1.0f);
            it_segunda_palabra++;
        }

        std::string tres_palabras = "";
        if (bolsa_de_palabras.cend() != it_tercera_palabra) {
            tres_palabras = dos_palabras + " " + *it_tercera_palabra;

            resultado_sentimiento->aumentarNegatividad(tres_palabras, 1.0f);
            it_tercera_palabra++;
        }
    }
}

void Sentimiento::aumentar_neutralidad(const std::vector<std::string>& bolsa_de_palabras, ResultadoSentimiento * resultado_sentimiento) {
    std::vector<std::string>::const_iterator it_segunda_palabra = bolsa_de_palabras.cbegin() + 1;
    std::vector<std::string>::const_iterator it_tercera_palabra = bolsa_de_palabras.cbegin() + 2;
    for (auto palabra : bolsa_de_palabras) {

        resultado_sentimiento->aumentarNeutralidad(palabra, 1.0f);

        std::string dos_palabras = "";
        if (bolsa_de_palabras.cend() != it_segunda_palabra) {
            dos_palabras = palabra + " " + *it_segunda_palabra;

            resultado_sentimiento->aumentarNeutralidad(dos_palabras, 1.0f);
            it_segunda_palabra++;
        }

        std::string tres_palabras = "";
        if (bolsa_de_palabras.cend() != it_tercera_palabra) {
            tres_palabras = dos_palabras + " " + *it_tercera_palabra;

            resultado_sentimiento->aumentarNeutralidad(tres_palabras, 1.0f);
            it_tercera_palabra++;
        }
    }
}

}
}
}