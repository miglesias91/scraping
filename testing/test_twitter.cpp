// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>
#include <sstream>

// twitter
#include <twitter/include/Aplicacion.h>
#include <twitter/include/Usuario.h>
#include <twitter/include/Tweet.h>

// herramenitas
#include <utiles/include/Json.h>
#include <utiles/include/Conversiones.h>

using namespace scraping::twitter;

TEST(ScrapingTwitter, obtenerUltimosTweets)
{
    //scraping::twitter::ConsumidorAPI * consumidor_api_twitter = new scraping::twitter::ConsumidorAPI("aXPpXInb16k0jKIswOYuUS3ly", "MhuDBpN9EtnafrIUHvJEbleJ3WKiFCSBIulwRVNvZTWoXGs2eV");
    //consumidor_api_twitter->obtenerTokenDeAcceso();

    //scraping::twitter::modelo::Aplicacion app(consumidor_api_twitter);

    //scraping::twitter::modelo::Usuario clarin("clarincom");

    //std::vector<scraping::twitter::modelo::Tweet> tweets = app.leerUltimosTweets(&clarin);

    //ASSERT_EQ(true, true);
}

TEST(ScrapingTwitter, parsearTweetsCorrectamente)
{
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
        tweets.push_back(nuevo_tweet);
    }

    std::string texto_correcto_tweet_1 = "Jerusal\u00e9n: suenan sirenas de alarma en el sur de Israel tras el disparo de un cohete desde Gaza\u2026 https:\/\/t.co\/eqSJm9AkQB";
    std::string texto_parseado_tweet_1 = tweets[0]->getTexto();
    std::string texto_parseado_tweet_1_convertido = herramientas::utiles::Conversiones::utf82iso8859_1(texto_parseado_tweet_1);

    for (std::vector<modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
    {
        delete *it;
    }

    ASSERT_EQ(texto_correcto_tweet_1.c_str(), texto_parseado_tweet_1.c_str());
}