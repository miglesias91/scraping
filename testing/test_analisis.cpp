// gtest
#include <gtest/gtest.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>

using namespace scraping::analisis;

TEST(Analisis, fuerzaEnNoticia)
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    //std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "sur", "israel", "disparo", "cohete", "gaza" };

    //std::vector<std::pair<std::string, float>> fuerzas_de_palabras_1 = fuerza_en_noticia.aplicar(bolsa_de_palabras_1);

    //ASSERT_STREQ("gaza", fuerzas_de_palabras_1[0].first.c_str());
    // ASSERT_EQ(1.732393, fuerzas_de_palabras_1[0].second);

    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    std::vector<std::pair<std::string, float>> fuerzas_de_palabras_2 = fuerza_en_noticia.aplicar(bolsa_de_palabras_2);

    ASSERT_STREQ("jerusalen", fuerzas_de_palabras_2[0].first.c_str());
    // ASSERT_EQ(1.732393, fuerzas_de_palabras_2[0].second);
}

TEST(Analisis, parsearTweetsCorrectamente)
{

}