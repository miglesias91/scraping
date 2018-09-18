
// catch2
#include <catch.hpp>

// scraping
#include <scraping/include/IAdministradorScraping.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/Sentimiento.h>
#include <analisis/include/ResultadoSentimiento.h>

// preparacion
#include <preparacion/include/ResultadoAnalisisContenido.h>

using namespace scraping::analisis;

TEST_CASE("fuerza_en_noticia_analizar", "analisis[.]")
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "sur", "israel", "disparo", "cohete", "gaza" };

    tecnicas::ResultadoFuerzaEnNoticia resultado_1;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_1, &resultado_1);

    REQUIRE(24 == resultado_1.cantidadDePalabras());
    REQUIRE(std::round(1000. * 1.73239374) == std::round(1000. * resultado_1.getFuerza("jerusalen")));
    REQUIRE(std::round(1000. * 1.73239374) == std::round(1000. * resultado_1.getFuerza("gaza")));
    REQUIRE(std::round(1000. * 1.73239374) == std::round(1000. * resultado_1.getFuerza("alarma sur")));
    
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "sur", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia resultado_2;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, &resultado_2);

    std::vector<std::pair<std::string, float>> top_10 = resultado_2.getTop(10);

    REQUIRE(28 == resultado_2.cantidadDePalabras());
    REQUIRE(std::round(1000. * 5.62518406) == std::round(1000. * resultado_2.getFuerza("jerusalen")));
    REQUIRE(std::round(1000. * 3.75012255) == std::round(1000. * resultado_2.getFuerza("israel")));
    REQUIRE(std::round(1000. * 3.75012255) == std::round(1000. * resultado_2.getFuerza("jerusalen sur")));
    REQUIRE(std::round(1000. * 1.87506127) == std::round(1000. * resultado_2.getFuerza("jerusalen suenan")));
    REQUIRE(std::round(1000. * 1.87506127) == std::round(1000. * resultado_2.getFuerza("gaza")));

}

TEST_CASE("fuerza_en_noticia_armar_json", "analisis[.]")
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia resultado;
    fuerza_en_noticia.aplicar(bolsa_de_palabras, &resultado);

    resultado.armarJson();

    std::string json_string = resultado.getJson()->jsonString();
    std::string json_string_correcto = "{\"valores\":[\"jerusalen_5.6763\",\"israel_3.7842\",\"suenan sirenas alarma_1.8921\",\"jerusalen suenan_1.8921\",\"suenan sirenas_1.8921\",\"jerusalen suenan sirenas_1.8921\",\"suenan_1.8921\",\"sirenas_1.8921\",\"sirenas alarma_1.8921\",\"sirenas alarma jerusalen_1.8921\",\"alarma_1.8921\",\"alarma jerusalen_1.8921\",\"jerusalen sur_1.8921\",\"alarma jerusalen sur_1.8921\",\"cohete gaza_1.8921\",\"jerusalen sur israel_1.8921\",\"israel disparo jerusalen_1.8921\",\"sur_1.8921\",\"sur israel_1.8921\",\"sur israel disparo_1.8921\",\"israel disparo_1.8921\",\"disparo_1.8921\",\"disparo jerusalen_1.8921\",\"disparo jerusalen cohete_1.8921\",\"jerusalen cohete_1.8921\",\"jerusalen cohete gaza_1.8921\",\"cohete_1.8921\",\"cohete gaza israel_1.8921\",\"gaza_1.8921\",\"gaza israel_1.8921\"]}";

    REQUIRE(json_string_correcto == json_string);

    tecnicas::ResultadoFuerzaEnNoticia resultado_nuevo;
    resultado_nuevo.setJson(new herramientas::utiles::Json(json_string_correcto));
    resultado_nuevo.parsearJson();

    REQUIRE(std::round(1000. * 5.67628384) == std::round(1000. * resultado.getFuerza("jerusalen")));
    REQUIRE(std::round(1000. * 3.78418922) == std::round(1000. * resultado.getFuerza("israel")));
    REQUIRE(std::round(1000. * 1.89209461) == std::round(1000. * resultado.getFuerza("gaza")));
    REQUIRE(std::round(1000. * 1.89209461) == std::round(1000. * resultado.getFuerza("suenan sirenas alarma")));
}

TEST_CASE("fuerza_en_noticia_sumar", "analisis[.]")
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel", "holis", "chau" };

    tecnicas::ResultadoFuerzaEnNoticia resultado_1;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_1, &resultado_1);

    tecnicas::ResultadoFuerzaEnNoticia resultado_2;
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, &resultado_2);

    resultado_1.sumarFuerzas(&resultado_2);

    REQUIRE(std::round(1000. * 11.4948416) == std::round(1000. * resultado_1.getFuerza("jerusalen")));
    REQUIRE(std::round(1000. * 7.66322803) == std::round(1000. * resultado_1.getFuerza("israel")));
    REQUIRE(std::round(1000. * 3.83161402) == std::round(1000. * resultado_1.getFuerza("gaza")));
    REQUIRE(std::round(1000. * 3.83161402) == std::round(1000. * resultado_1.getFuerza("jerusalen sur")));
    REQUIRE(std::round(1000. * 1.93951929) == std::round(1000. * resultado_1.getFuerza("holis")));
    REQUIRE(std::round(1000. * 1.93951929) == std::round(1000. * resultado_1.getFuerza("chau")));
    REQUIRE(std::round(1000. * 1.93951929) == std::round(1000. * resultado_1.getFuerza("holis chau")));
    REQUIRE(std::round(1000. * 1.93951929) == std::round(1000. * resultado_1.getFuerza("israel holis chau")));
}

TEST_CASE("combinar_resultados", "analisis[.]")
{
    tecnicas::Sentimiento::cargar("config_sentimiento.json");

    tecnicas::FuerzaEnNoticia fuerza_en_noticia;
    tecnicas::Sentimiento sentimiento;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel", "holis", "chau" };

    tecnicas::ResultadoFuerzaEnNoticia * resultado_1 = new tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_1, resultado_1);
    
    tecnicas::ResultadoSentimiento * resultado_sentimiento_1 = new tecnicas::ResultadoSentimiento();
    sentimiento.aplicar(bolsa_de_palabras_1, resultado_sentimiento_1);

    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_1(resultado_1, resultado_sentimiento_1);

    tecnicas::ResultadoFuerzaEnNoticia * resultado_2 = new tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, resultado_2);

    tecnicas::ResultadoSentimiento * resultado_sentimiento_2 = new tecnicas::ResultadoSentimiento();
    sentimiento.aplicar(bolsa_de_palabras_2, resultado_sentimiento_2);

    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_2(resultado_2, resultado_sentimiento_2);

    resultado_analisis_1.combinarCon(&resultado_analisis_2);
    
    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia_combinado = resultado_analisis_1.getResultadoFuerzaEnNoticia();

    REQUIRE(std::round(1000. * 11.4948416) == std::round(1000. * resultado_fuerza_en_noticia_combinado->getFuerza("jerusalen")));
    REQUIRE(std::round(1000. * 7.66322803) == std::round(1000. * resultado_fuerza_en_noticia_combinado->getFuerza("israel")));
    REQUIRE(std::round(1000. * 3.83161402) == std::round(1000. * resultado_fuerza_en_noticia_combinado->getFuerza("gaza")));
    REQUIRE(std::round(1000. * 3.83161402) == std::round(1000. * resultado_fuerza_en_noticia_combinado->getFuerza("gaza israel")));
    REQUIRE(std::round(1000. * 1.93951929) == std::round(1000. * resultado_fuerza_en_noticia_combinado->getFuerza("holis")));
    REQUIRE(std::round(1000. * 1.93951929) == std::round(1000. * resultado_fuerza_en_noticia_combinado->getFuerza("chau")));
    REQUIRE(std::round(1000. * 1.93951929) == std::round(1000. * resultado_fuerza_en_noticia_combinado->getFuerza("holis chau")));

    tecnicas::ResultadoSentimiento * resultado_sentimiento_combinado = resultado_analisis_1.getResultadoSentimiento();

    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("jerusalen").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("jerusalen").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("suenan sirenas").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("suenan sirenas").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->negatividad("israel").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->negatividad("israel").cantidad));
    REQUIRE(std::round(1000. * 2) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("gaza").suma));
    REQUIRE(std::round(1000. * 2) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("gaza").cantidad));
    REQUIRE(std::round(1000. * 2) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("jerusalen sur").suma));
    REQUIRE(std::round(1000. * 2) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("jerusalen sur").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("holis").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("holis").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("chau").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("chau").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("holis chau").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("holis chau").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("holis chau").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("holis chau").cantidad));
}

TEST_CASE("armar_json_resultados", "analisis[.]")
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;
    tecnicas::Sentimiento sentimiento;

    std::vector<std::string> bolsa_de_palabras = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras, resultado_fuerza_en_noticia);

    tecnicas::ResultadoSentimiento * resultado_sentimiento_1 = new tecnicas::ResultadoSentimiento();
    sentimiento.aplicar(bolsa_de_palabras, resultado_sentimiento_1);

    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis(resultado_fuerza_en_noticia, resultado_sentimiento_1);

    resultado_analisis.armarJson();

    std::string json_string = resultado_analisis.getJson()->jsonString();
    std::string json_string_correcto = "{\"fuerza_en_noticia\":{\"valores\":[\"jerusalen_5.6763\",\"israel_3.7842\",\"suenan sirenas alarma_1.8921\",\"jerusalen suenan_1.8921\",\"suenan sirenas_1.8921\",\"jerusalen suenan sirenas_1.8921\",\"suenan_1.8921\",\"sirenas_1.8921\",\"sirenas alarma_1.8921\",\"sirenas alarma jerusalen_1.8921\",\"alarma_1.8921\",\"alarma jerusalen_1.8921\",\"jerusalen sur_1.8921\",\"alarma jerusalen sur_1.8921\",\"cohete gaza_1.8921\",\"jerusalen sur israel_1.8921\",\"israel disparo jerusalen_1.8921\",\"sur_1.8921\",\"sur israel_1.8921\",\"sur israel disparo_1.8921\",\"israel disparo_1.8921\",\"disparo_1.8921\",\"disparo jerusalen_1.8921\",\"disparo jerusalen cohete_1.8921\",\"jerusalen cohete_1.8921\",\"jerusalen cohete gaza_1.8921\",\"cohete_1.8921\",\"cohete gaza israel_1.8921\",\"gaza_1.8921\",\"gaza israel_1.8921\"]},\"sentimiento\":{\"valores\":[\"jerusalen_0/0-0/0-3/3\",\"israel_0/0-0/0-2/2\",\"suenan sirenas alarma_0/0-0/0-1/1\",\"suenan sirenas_0/0-0/0-1/1\",\"jerusalen suenan_0/0-0/0-1/1\",\"suenan_0/0-0/0-1/1\",\"jerusalen suenan sirenas_0/0-0/0-1/1\",\"sirenas_0/0-0/0-1/1\",\"sirenas alarma_0/0-0/0-1/1\",\"sirenas alarma jerusalen_0/0-0/0-1/1\",\"alarma_0/0-0/0-1/1\",\"jerusalen sur_0/0-0/0-1/1\",\"alarma jerusalen_0/0-0/0-1/1\",\"cohete gaza_0/0-0/0-1/1\",\"alarma jerusalen sur_0/0-0/0-1/1\",\"israel disparo jerusalen_0/0-0/0-1/1\",\"jerusalen sur israel_0/0-0/0-1/1\",\"sur_0/0-0/0-1/1\",\"sur israel_0/0-0/0-1/1\",\"sur israel disparo_0/0-0/0-1/1\",\"israel disparo_0/0-0/0-1/1\",\"disparo_0/0-0/0-1/1\",\"disparo jerusalen_0/0-0/0-1/1\",\"disparo jerusalen cohete_0/0-0/0-1/1\",\"jerusalen cohete_0/0-0/0-1/1\",\"jerusalen cohete gaza_0/0-0/0-1/1\",\"cohete_0/0-0/0-1/1\",\"cohete gaza israel_0/0-0/0-1/1\",\"gaza_0/0-0/0-1/1\",\"gaza israel_0/0-0/0-1/1\"]},\"fecha\":\"00000000000000\",\"categoria\":\"\"}";

    REQUIRE(json_string_correcto == json_string);

    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_nuevo;
    resultado_analisis_nuevo.setJson(new herramientas::utiles::Json(json_string_correcto));
    resultado_analisis_nuevo.parsearJson();

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia_nuevo = resultado_analisis_nuevo.getResultadoFuerzaEnNoticia();

    REQUIRE(std::round(1000. * 5.67628384) == std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("jerusalen")));
    REQUIRE(std::round(1000. * 3.78418922) == std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("israel")));
    REQUIRE(std::round(1000. * 1.89209461) == std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("gaza")));
    REQUIRE(std::round(1000. * 1.89209461) == std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("suenan sirenas alarma")));

    tecnicas::ResultadoSentimiento * resultado_sentimiento_combinado = resultado_analisis_nuevo.getResultadoSentimiento();

    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("jerusalen").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("jerusalen").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->negatividad("israel").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->negatividad("israel").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("gaza").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("gaza").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("suenan sirenas alarma").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("suenan sirenas alarma").cantidad));
}

TEST_CASE("almacenar_y_recuperar_resultados", "analisis[.]")
{
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;
    tecnicas::Sentimiento sentimiento;

    std::vector<std::string> bolsa_de_palabras = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras, resultado_fuerza_en_noticia);

    tecnicas::ResultadoSentimiento * resultado_sentimiento_1 = new tecnicas::ResultadoSentimiento();
    sentimiento.aplicar(bolsa_de_palabras, resultado_sentimiento_1);

    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis(resultado_fuerza_en_noticia, resultado_sentimiento_1);
    resultado_analisis.setId(new herramientas::utiles::ID(123));

    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenar(&resultado_analisis);

    // recupero lo que acabo de almacenar.
    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_a_recuperar;
    resultado_analisis_a_recuperar.setId(resultado_analisis.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperar(&resultado_analisis_a_recuperar);

    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia_nuevo = resultado_analisis_a_recuperar.getResultadoFuerzaEnNoticia();

    REQUIRE(std::round(1000. * 5.67628384) == std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("jerusalen")));
    REQUIRE(std::round(1000. * 3.78418922) == std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("israel")));
    REQUIRE(std::round(1000. * 1.89209461) == std::round(1000. * resultado_fuerza_en_noticia_nuevo->getFuerza("gaza")));

    tecnicas::ResultadoSentimiento * resultado_sentimiento_combinado = resultado_analisis_a_recuperar.getResultadoSentimiento();

    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("jerusalen").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->positividad("jerusalen").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->negatividad("israel").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_sentimiento_combinado->negatividad("israel").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("gaza").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_sentimiento_combinado->neutralidad("gaza").cantidad));
}


TEST_CASE("sentimiento_analisis_correcto", "analisis[.]")
{
    tecnicas::Sentimiento sentimiento;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "sur", "israel", "disparo", "cohete", "gaza" };

    tecnicas::ResultadoSentimiento resultado_1;
    sentimiento.aplicar(bolsa_de_palabras_1, &resultado_1);

    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.positividad("jerusalen").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.positividad("jerusalen").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.negatividad("israel").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.negatividad("israel").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_1.neutralidad("gaza").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_1.neutralidad("gaza").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_1.neutralidad("suenan sirenas").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_1.neutralidad("suenan sirenas").cantidad));
}

TEST_CASE("resultado_sentimiento_armar_json_correctamente", "analisis[.]")
{
    tecnicas::Sentimiento sentimiento;

    std::vector<std::string> bolsa_de_palabras = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };

    tecnicas::ResultadoSentimiento resultado;
    sentimiento.aplicar(bolsa_de_palabras, &resultado);

    resultado.armarJson();

    std::string json_string = resultado.getJson()->jsonString();
    std::string json_string_correcto = "{\"valores\":[\"jerusalen_0/0-0/0-3/3\",\"israel_0/0-0/0-2/2\",\"suenan sirenas alarma_0/0-0/0-1/1\",\"suenan sirenas_0/0-0/0-1/1\",\"jerusalen suenan_0/0-0/0-1/1\",\"suenan_0/0-0/0-1/1\",\"jerusalen suenan sirenas_0/0-0/0-1/1\",\"sirenas_0/0-0/0-1/1\",\"sirenas alarma_0/0-0/0-1/1\",\"sirenas alarma jerusalen_0/0-0/0-1/1\",\"alarma_0/0-0/0-1/1\",\"jerusalen sur_0/0-0/0-1/1\",\"alarma jerusalen_0/0-0/0-1/1\",\"cohete gaza_0/0-0/0-1/1\",\"alarma jerusalen sur_0/0-0/0-1/1\",\"israel disparo jerusalen_0/0-0/0-1/1\",\"jerusalen sur israel_0/0-0/0-1/1\",\"sur_0/0-0/0-1/1\",\"sur israel_0/0-0/0-1/1\",\"sur israel disparo_0/0-0/0-1/1\",\"israel disparo_0/0-0/0-1/1\",\"disparo_0/0-0/0-1/1\",\"disparo jerusalen_0/0-0/0-1/1\",\"disparo jerusalen cohete_0/0-0/0-1/1\",\"jerusalen cohete_0/0-0/0-1/1\",\"jerusalen cohete gaza_0/0-0/0-1/1\",\"cohete_0/0-0/0-1/1\",\"cohete gaza israel_0/0-0/0-1/1\",\"gaza_0/0-0/0-1/1\",\"gaza israel_0/0-0/0-1/1\"]}";

    REQUIRE(json_string_correcto == json_string);

    tecnicas::ResultadoSentimiento resultado_nuevo;
    resultado_nuevo.setJson(new herramientas::utiles::Json(json_string_correcto));
    resultado_nuevo.parsearJson();

    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_nuevo.positividad("jerusalen").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_nuevo.positividad("jerusalen").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_nuevo.negatividad("israel").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_nuevo.negatividad("israel").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_nuevo.neutralidad("gaza").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_nuevo.neutralidad("gaza").cantidad));
}

TEST_CASE("resultado_sentimiento_sumar_correctamente", "analisis[.]")
{
    tecnicas::Sentimiento sentimiento;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel", "holis", "chau" };

    tecnicas::ResultadoSentimiento resultado_1;
    sentimiento.aplicar(bolsa_de_palabras_1, &resultado_1);

    tecnicas::ResultadoSentimiento resultado_2;
    sentimiento.aplicar(bolsa_de_palabras_2, &resultado_2);

    resultado_1.sumar(&resultado_2);

    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.positividad("jerusalen").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.positividad("jerusalen").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.negatividad("israel").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.negatividad("israel").cantidad));
    REQUIRE(std::round(1000. * 2) == std::round(1000. * resultado_1.neutralidad("gaza").suma));
    REQUIRE(std::round(1000. * 2) == std::round(1000. * resultado_1.neutralidad("gaza").cantidad));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.positividad("holis").suma));
    REQUIRE(std::round(1000. * 0) == std::round(1000. * resultado_1.positividad("holis").cantidad));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_1.neutralidad("chau").suma));
    REQUIRE(std::round(1000. * 1) == std::round(1000. * resultado_1.neutralidad("chau").cantidad));
}
