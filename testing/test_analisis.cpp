// gtest
#include <gtest/gtest.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>

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

TEST(Analisis, fuerzaEnNoticiaArmarJsonCorrectamente)
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia resultado_2;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, resultado_2);

    resultado_2.armarJson();

    std::string json_string = resultado_2.getJson()->jsonString();
    std::string json_string_correcto = "{\"jerusalen\":}";

    //ASSERT_STREQ()
}