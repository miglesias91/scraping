// gtest
#include <gtest/gtest.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoAnalisis.h>

using namespace scraping::analisis;

TEST(Analisis, fuerzaEnNoticia)
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "sur", "israel", "disparo", "cohete", "gaza" };

    tecnicas::ResultadoFuerzaEnNoticia resultado_1;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_1, resultado_1);

    ASSERT_EQ(9, resultado_1.cantidadDePalabras());
    ASSERT_EQ(std::round(1000. * 1.73239374), std::round(1000. * resultado_1.getFuerza("jerusalen")));
    ASSERT_EQ(std::round(1000. * 1.73239374), std::round(1000. * resultado_1.getFuerza("gaza")));
    
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia resultado_2;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, resultado_2);
    
    ASSERT_EQ(9, resultado_2.cantidadDePalabras());
    ASSERT_EQ(std::round(1000. * 5.67628384), std::round(1000. * resultado_2.getFuerza("jerusalen")));
    ASSERT_EQ(std::round(1000. * 3.78418922), std::round(1000. * resultado_2.getFuerza("israel")));
    ASSERT_EQ(std::round(1000. * 1.89209461), std::round(1000. * resultado_2.getFuerza("gaza")));

    std::vector<std::pair<std::string, float>> top_3 = resultado_2.getTop(3);
}

TEST(Analisis, resultadoFuerzaEnNoticiaArmarJsonCorrectamente)
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia resultado;
    fuerza_en_noticia.aplicar(bolsa_de_palabras, resultado);

    resultado.armarJson();

    std::string json_string = resultado.getJson()->jsonString();
    std::string json_string_correcto = "{\"valores\":[\"jerusalen_5.6763\",\"israel_3.7842\",\"gaza_1.8921\",\"suenan_1.8921\",\"sur_1.8921\",\"sirenas_1.8921\",\"alarma_1.8921\",\"disparo_1.8921\",\"cohete_1.8921\"]}";

    ASSERT_STREQ(json_string_correcto.c_str(), json_string.c_str());

    tecnicas::ResultadoFuerzaEnNoticia resultado_nuevo;
    resultado_nuevo.setJson(new herramientas::utiles::Json(json_string_correcto));
    resultado_nuevo.parsearJson();

    ASSERT_EQ(std::round(1000. * 5.67628384), std::round(1000. * resultado.getFuerza("jerusalen")));
    ASSERT_EQ(std::round(1000. * 3.78418922), std::round(1000. * resultado.getFuerza("israel")));
    ASSERT_EQ(std::round(1000. * 1.89209461), std::round(1000. * resultado.getFuerza("gaza")));
}

TEST(Analisis, resultadoAnalisisArmarJsonCorrectamente)
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras, *resultado_fuerza_en_noticia);

    ResultadoAnalisis resultado_analisis(resultado_fuerza_en_noticia);

    resultado_analisis.armarJson();

    std::string json_string = resultado_analisis.getJson()->jsonString();
    std::string json_string_correcto = "{\"fuerza_en_noticia\":{\"valores\":[\"jerusalen_5.6763\",\"israel_3.7842\",\"gaza_1.8921\",\"suenan_1.8921\",\"sur_1.8921\",\"sirenas_1.8921\",\"alarma_1.8921\",\"disparo_1.8921\",\"cohete_1.8921\"]}}";

    ASSERT_STREQ(json_string_correcto.c_str(), json_string.c_str());

    ResultadoAnalisis resultado_analisis_nuevo;
    resultado_analisis_nuevo.setJson(new herramientas::utiles::Json(json_string_correcto));
    resultado_analisis_nuevo.parsearJson();

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia_nuevo = resultado_analisis_nuevo.getResultadoFuerzaEnNoticia();

    ASSERT_EQ(std::round(1000. * 5.67628384), std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("jerusalen")));
    ASSERT_EQ(std::round(1000. * 3.78418922), std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("israel")));
    ASSERT_EQ(std::round(1000. * 1.89209461), std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("gaza")));
}