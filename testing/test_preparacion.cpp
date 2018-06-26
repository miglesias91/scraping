// catch2
#include <catch.hpp>

// scraping
#include <scraping/include/IAdministradorScraping.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/Sentimiento.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/ResultadoSentimiento.h>

// preparacion
#include <preparacion/include/ResultadoAnalisisMedio.h>
#include <preparacion/include/ResultadoAnalisisContenido.h>
#include <preparacion/include/ResultadoAnalisisDiario.h>

using namespace scraping::preparacion;

TEST_CASE("almacenar_y_recuperar_resultado_analisis_medio_correctamente", "preparacion")
{
    scraping::analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia;
    scraping::analisis::tecnicas::Sentimiento sentimiento;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel", "holis", "chau" };

    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_1 = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_1, resultado_1);

    scraping::analisis::tecnicas::ResultadoSentimiento * resultado_1_sentimiento = new scraping::analisis::tecnicas::ResultadoSentimiento();
    sentimiento.aplicar(bolsa_de_palabras_1, resultado_1_sentimiento);

    scraping::preparacion::ResultadoAnalisisMedio resultado_analisis_1(resultado_1);
    resultado_analisis_1.setResultadoSentimiento(resultado_1_sentimiento);
    resultado_analisis_1.setId(new herramientas::utiles::ID(1234));

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&resultado_analisis_1);

    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_2 = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, resultado_2);

    scraping::analisis::tecnicas::ResultadoSentimiento * resultado_2_sentimiento = new scraping::analisis::tecnicas::ResultadoSentimiento();
    sentimiento.aplicar(bolsa_de_palabras_2, resultado_2_sentimiento);

    scraping::preparacion::ResultadoAnalisisMedio resultado_analisis_2(resultado_2);
    resultado_analisis_2.setResultadoSentimiento(resultado_2_sentimiento);
    resultado_analisis_2.setId(new herramientas::utiles::ID(4321));

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&resultado_analisis_2);

    // recupero los resultados de medios almacenados y los combino.

    scraping::preparacion::ResultadoAnalisisMedio resultado_analisis_1_recuperado;
    resultado_analisis_1_recuperado.setId(resultado_analisis_1.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultado_analisis_1_recuperado);

    scraping::preparacion::ResultadoAnalisisMedio resultado_analisis_2_recuperado;
    resultado_analisis_2_recuperado.setId(resultado_analisis_2.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultado_analisis_2_recuperado);

    resultado_analisis_1_recuperado.combinarCon(&resultado_analisis_2_recuperado);

    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia_combinado = resultado_analisis_1_recuperado.getResultadoFuerzaEnNoticia();

    REQUIRE(std::round(100. * 11.4948416) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("jerusalen")));
    REQUIRE(std::round(100. * 7.66322803) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("israel")));
    REQUIRE(std::round(100. * 3.83161402) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("gaza")));
    REQUIRE(std::round(100. * 1.93951929) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("holis")));
    REQUIRE(std::round(100. * 1.93951929) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("chau")));
}

TEST_CASE("almacenar_y_recuperar_resultado_analisis_contenido_correctamente", "preparacion")
{
    scraping::analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel", "holis", "chau" };

    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_1 = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_1, resultado_1);
    
    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_1(resultado_1);
    resultado_analisis_1.setId(new herramientas::utiles::ID(1234));

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&resultado_analisis_1);

    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_2 = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, resultado_2);
    
    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_2(resultado_2);
    resultado_analisis_2.setId(new herramientas::utiles::ID(4321));

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&resultado_analisis_2);

    // recupero los resultados de contenidos almacenados y los combino.

    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_1_recuperado;
    resultado_analisis_1_recuperado.setId(resultado_analisis_1.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultado_analisis_1_recuperado);

    scraping::preparacion::ResultadoAnalisisContenido resultado_analisis_2_recuperado;
    resultado_analisis_2_recuperado.setId(resultado_analisis_2.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultado_analisis_2_recuperado);

    resultado_analisis_1_recuperado.combinarCon(&resultado_analisis_2_recuperado);

    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia_combinado = resultado_analisis_1_recuperado.getResultadoFuerzaEnNoticia();

    REQUIRE(std::round(100. * 11.4948416) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("jerusalen")));
    REQUIRE(std::round(100. * 7.66322803) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("israel")));
    REQUIRE(std::round(100. * 3.83161402) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("gaza")));
    REQUIRE(std::round(100. * 1.93951929) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("holis")));
    REQUIRE(std::round(100. * 1.93951929) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("chau")));
}

TEST_CASE("almacenar_y_recuperar_resultado_analisis_diario_correctamente", "preparacion")
{
    scraping::analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia;

    std::vector<std::string> bolsa_de_palabras_1 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel" };
    std::vector<std::string> bolsa_de_palabras_2 = { "jerusalen", "suenan", "sirenas", "alarma", "jerusalen", "sur", "israel", "disparo", "jerusalen", "cohete", "gaza", "israel", "holis", "chau" };

    scraping::preparacion::ResultadoAnalisisDiario resultado_diario;
    resultado_diario.setId(new herramientas::utiles::ID(1));

    // medio 1
    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_1 = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_1, resultado_1);

    scraping::preparacion::ResultadoAnalisisMedio * resultado_analisis_1 = new scraping::preparacion::ResultadoAnalisisMedio(resultado_1);
    resultado_analisis_1->setId(new herramientas::utiles::ID(1234));

    resultado_diario.agregarResultadoDeMedio(resultado_analisis_1);

    // medio 2
    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_2 = new scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(bolsa_de_palabras_2, resultado_2);

    scraping::preparacion::ResultadoAnalisisMedio * resultado_analisis_2 = new scraping::preparacion::ResultadoAnalisisMedio(resultado_2);
    resultado_analisis_2->setId(new herramientas::utiles::ID(4321));

    resultado_diario.agregarResultadoDeMedio(resultado_analisis_2);

    // almacena el resultado diario
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&resultado_diario);

    // lo recupero en otro resultado creado
    scraping::preparacion::ResultadoAnalisisDiario resultado_diario_recuperado;
    resultado_diario_recuperado.setId(resultado_diario.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&resultado_diario_recuperado);

    scraping::preparacion::ResultadoAnalisisMedio * resultado_analisis_recuperado_1 = resultado_diario_recuperado.getResultadoMedio(resultado_analisis_1->getId()->numero());

    scraping::preparacion::ResultadoAnalisisMedio * resultado_analisis_recuperado_2 = resultado_diario_recuperado.getResultadoMedio(resultado_analisis_2->getId()->numero());

    resultado_analisis_recuperado_1->combinarCon(resultado_analisis_recuperado_2);

    scraping::analisis::tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia_combinado = resultado_analisis_recuperado_1->getResultadoFuerzaEnNoticia();

    delete resultado_analisis_1;
    delete resultado_analisis_2;

    REQUIRE(std::round(100. * 11.4948416) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("jerusalen")));
    REQUIRE(std::round(100. * 7.66322803) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("israel")));
    REQUIRE(std::round(100. * 3.83161402) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("gaza")));
    REQUIRE(std::round(100. * 1.93951929) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("holis")));
    REQUIRE(std::round(100. * 1.93951929) == std::round(100. * resultado_fuerza_en_noticia_combinado->getFuerza("chau")));
}

