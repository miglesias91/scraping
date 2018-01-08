// gtest
#include <gtest/gtest.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>

// twitter
#include <twitter/include/Aplicacion.h>
#include <twitter/include/Cuenta.h>
#include <twitter/include/Tweet.h>

using namespace scraping::twitter;

TEST(Extraccion, almacenarYRecuperarCorrectamente)
{
    // probar almacenar y recuperar una cuenta de twitter como Medio, y los tweets como Contenidos.
    // agregarles los Tweets leidos desde disco. a partir de ahi hacer que se almacene el Medio (1 registro) y los Contenidos (1 registro por cada medio),
    // y que despues se puedan acceder tanto el Medio como los Contenidos por separados.

    scraping::ConfiguracionScraping::leerConfiguracion("config_scraping.json");

    scraping::extraccion::Medio::getGestorIDs()->setIdActual(100);
    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(200);

    modelo::Cuenta cuenta("clarin");
    cuenta.asignarNuevoId();

    std::ifstream archivo_tweets("tweets_de_prueba.txt");

    std::stringstream sstream;
    sstream << archivo_tweets.rdbuf();

    std::string string_tweets(sstream.str());

    herramientas::utiles::Json json_tweets(string_tweets);

    std::vector<herramientas::utiles::Json*> tweets_json = json_tweets.getAtributoArrayJson();

    std::vector<modelo::Tweet*> tweets;
    modelo::Tweet* nuevo_tweet = NULL;
    for (std::vector<herramientas::utiles::Json*>::iterator it = tweets_json.begin(); it != tweets_json.end(); it++)
    {
        nuevo_tweet = new modelo::Tweet(*it);
        nuevo_tweet->asignarNuevoId();

        tweets.push_back(nuevo_tweet);

        cuenta.agregarContenidoParaAnalizar(nuevo_tweet);
    }

    std::vector<unsigned long long int> ids_tweets = cuenta.getIDsContenidosNoAnalizados();

    ASSERT_EQ(100, cuenta.getId()->numero());

    ASSERT_EQ(200, ids_tweets[0]);
    ASSERT_EQ(201, ids_tweets[1]);
    ASSERT_EQ(202, ids_tweets[2]);
    ASSERT_EQ(203, ids_tweets[3]);
    ASSERT_EQ(204, ids_tweets[4]);

    // almaceno el medio (cuenta twitter).
    scraping::IAdministradorScraping::getInstancia()->almacenar(&cuenta);

    // almaceno los contenidos del medio (tweets de la cuenta).
    for (std::vector<modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
    {
        scraping::IAdministradorScraping::getInstancia()->almacenar(*it);
    }

    // recupero el medio.
    modelo::Cuenta cuenta_recuperada;
    cuenta_recuperada.setId(cuenta.getId()->copia());

    scraping::IAdministradorScraping::getInstancia()->recuperar(&cuenta_recuperada);

    // recupero los contenidos del medio.
    modelo::Tweet tweet_recuperado_1;
    tweet_recuperado_1.setId(tweets[0]->getId()->copia());
    scraping::IAdministradorScraping::getInstancia()->recuperar(&tweet_recuperado_1);

    modelo::Tweet tweet_recuperado_2;
    tweet_recuperado_2.setId(tweets[1]->getId()->copia());
    scraping::IAdministradorScraping::getInstancia()->recuperar(&tweet_recuperado_2);

    modelo::Tweet tweet_recuperado_3;
    tweet_recuperado_3.setId(tweets[2]->getId()->copia());
    scraping::IAdministradorScraping::getInstancia()->recuperar(&tweet_recuperado_3);

    modelo::Tweet tweet_recuperado_4;
    tweet_recuperado_4.setId(tweets[3]->getId()->copia());
    scraping::IAdministradorScraping::getInstancia()->recuperar(&tweet_recuperado_4);

    modelo::Tweet tweet_recuperado_5;
    tweet_recuperado_5.setId(tweets[4]->getId()->copia());
    scraping::IAdministradorScraping::getInstancia()->recuperar(&tweet_recuperado_5);

    ASSERT_EQ(cuenta.getNombre(), cuenta_recuperada.getNombre());

    ASSERT_EQ(tweets[0]->getIdTweet(), tweet_recuperado_1.getIdTweet());
    ASSERT_EQ(tweets[1]->getIdTweet(), tweet_recuperado_2.getIdTweet());
    ASSERT_EQ(tweets[2]->getIdTweet(), tweet_recuperado_3.getIdTweet());
    ASSERT_EQ(tweets[3]->getIdTweet(), tweet_recuperado_4.getIdTweet());
    ASSERT_EQ(tweets[4]->getIdTweet(), tweet_recuperado_5.getIdTweet());

    ASSERT_EQ(tweets[0]->getTexto(), tweet_recuperado_1.getTexto());
    ASSERT_EQ(tweets[1]->getTexto(), tweet_recuperado_2.getTexto());
    ASSERT_EQ(tweets[2]->getTexto(), tweet_recuperado_3.getTexto());
    ASSERT_EQ(tweets[3]->getTexto(), tweet_recuperado_4.getTexto());
    ASSERT_EQ(tweets[4]->getTexto(), tweet_recuperado_5.getTexto());

    for (std::vector<modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
    {
        delete *it;
    }
}