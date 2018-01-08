// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

// depuracion
#include <depuracion/include/Depurador.h>
#include <depuracion/include/DepurableTweet.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>

// twitter
#include <twitter/include/Tweet.h>

using namespace scraping;

TEST(Scraping, levantarConfigCorrectamente)
{
    ConfiguracionScraping::leerConfiguracion("config_scraping.json");

    ASSERT_EQ(true, ConfiguracionScraping::scrapingLocal());
    ASSERT_EQ(false, ConfiguracionScraping::scrapingDistribuido());

    ASSERT_EQ("001", ConfiguracionScraping::prefijoMedio());
    ASSERT_EQ("002", ConfiguracionScraping::prefijoContenido());
    ASSERT_EQ("003", ConfiguracionScraping::prefijoResultado());
}

TEST(Scraping, depurarAnalizarPreparar)
{
	// ----- EXTRACCION (simulada) ----- //

	std::ifstream archivo_le_doy_mi_palabra("le_doy_mi_palabra_20171222.txt");

    std::stringstream sstream;
    sstream << archivo_le_doy_mi_palabra.rdbuf();

    std::string texto_le_doy_mi_palabra(sstream.str());

    // ----- DEPURACION ----- //

    depuracion::Depurador depurador;
    depurador.cargarMapeoUTF8("mapeo_utf8.json");

    twitter::modelo::Tweet tweet;
    tweet.setTexto(texto_le_doy_mi_palabra);

    depuracion::DepurableTweet depurable_tweet(tweet);

    depuracion::ContenidoDepurado contenido_depurado = depurador.depurar(&depurable_tweet);

    std::vector<std::string> bolsa_de_palabras = contenido_depurado.getBolsaDePalabras();

    // ----- ANALISIS ----- //

    analisis::tecnicas::FuerzaEnNoticia fuerza_en_noticia(10);

    analisis::tecnicas::ResultadoFuerzaEnNoticia resultado_1;

    fuerza_en_noticia.aplicar(bolsa_de_palabras, resultado_1);

    std::vector<std::pair<std::string, float>> top_20 = resultado_1.getTop(20);

    // TODO: guardar

    // ----- PREPARACION ----- //
}