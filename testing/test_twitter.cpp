// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>
#include <sstream>

// scraping
#include <scraping/include/IAdministradorScraping.h>

// twitter
#include <twitter/include/Aplicacion.h>
#include <twitter/include/Cuenta.h>
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

    unsigned long long int id_parseado_tweet_1 = tweets[0]->getIdTweet();
    std::string texto_parseado_tweet_1 = tweets[0]->getTexto();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_tweet_1 = tweets[0]->getFechaCreacion();
    unsigned long long int id_usuario_parseado_tweet_1 = tweets[0]->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_tweet_1 = tweets[0] ->getHashtags().size();

    unsigned long long int id_correcto_tweet_1 = 708067963060916224;
    std::string texto_correcto_tweet_1 = "@jeremycloud Who would win in a battle between a Barred Owl and a Cooper's Hawk? https://t.co/FamikDro2h";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_tweet_1(10, 1, 2016, 23, 12, 12);
    unsigned long long int id_usuario_correcto_tweet_1 = 4449621923;
    unsigned int tamanio_vector_hashtags_correcto_tweet_1 = 0;

    for (std::vector<modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
    {
        delete *it;
    }

    ASSERT_EQ(id_correcto_tweet_1, id_parseado_tweet_1);
    ASSERT_STREQ(texto_correcto_tweet_1.c_str(), texto_parseado_tweet_1.c_str());
    ASSERT_EQ(true, fecha_de_creacion_correcta_tweet_1 == fecha_de_creacion_parseada_tweet_1);
    ASSERT_EQ(id_usuario_correcto_tweet_1, id_usuario_parseado_tweet_1);
    ASSERT_EQ(tamanio_vector_hashtags_correcto_tweet_1, tamanio_vector_hashtags_parseado_tweet_1);
}

TEST(ScrapingTwitter, parsearRetweetsCorrectamente)
{
    std::ifstream archivo_tweets("retweets_de_prueba.txt");

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

    // datos tweet
    unsigned long long int id_parseado_tweet_1 = tweets[0]->getIdTweet();
    std::string texto_parseado_tweet_1 = tweets[0]->getTexto();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_tweet_1 = tweets[0]->getFechaCreacion();
    unsigned long long int id_usuario_parseado_tweet_1 = tweets[0]->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_tweet_1 = tweets[0]->getHashtags().size();

    unsigned long long int id_correcto_tweet_1 = 958491763248893952;
    std::string texto_correcto_tweet_1 = "#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @CFKArgentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional  \nhttps://t.co/ptle5JWGte https://t.co/rM23gXjjqg";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_tweet_1(31, 1, 2018, 0, 6, 58);
    unsigned long long int id_usuario_correcto_tweet_1 = 138814032;
    unsigned int tamanio_vector_hashtags_correcto_tweet_1 = 1;

    // datos retweet
    unsigned long long int id_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getIdTweet();
    std::string texto_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getTexto();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_retweet_1 = tweets[0]->getTweetRetweeteado()->getFechaCreacion();
    unsigned long long int id_usuario_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getHashtags().size();

    unsigned long long int id_correcto_retweet_1 = 958483263634444292;
    std::string texto_correcto_retweet_1 = "#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @CFKArgentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional  \nhttps://t.co/ptle5JWGte https://t.co/rM23gXjjqg";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_retweet_1(30, 1, 2018, 23, 33, 12);
    unsigned long long int id_usuario_correcto_retweet_1 = 884164880114343937;
    unsigned int tamanio_vector_hashtags_correcto_retweet_1 = 1;

    for (std::vector<modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
    {
        delete *it;
    }

    ASSERT_EQ(id_correcto_tweet_1, id_parseado_tweet_1);
    ASSERT_STREQ(texto_correcto_tweet_1.c_str(), texto_parseado_tweet_1.c_str());
    ASSERT_EQ(true, fecha_de_creacion_correcta_tweet_1 == fecha_de_creacion_parseada_tweet_1);
    ASSERT_EQ(id_usuario_correcto_tweet_1, id_usuario_parseado_tweet_1);
    ASSERT_EQ(tamanio_vector_hashtags_correcto_tweet_1, tamanio_vector_hashtags_parseado_tweet_1);

    ASSERT_EQ(id_correcto_retweet_1, id_parseado_retweet_1);
    ASSERT_STREQ(texto_correcto_retweet_1.c_str(), texto_parseado_retweet_1.c_str());
    ASSERT_EQ(true, fecha_de_creacion_correcta_retweet_1 == fecha_de_creacion_parseada_retweet_1);
    ASSERT_EQ(id_usuario_correcto_retweet_1, id_usuario_parseado_retweet_1);
    ASSERT_EQ(tamanio_vector_hashtags_correcto_retweet_1, tamanio_vector_hashtags_parseado_retweet_1);
}


TEST(ScrapingTwitter, almacenarYRecuperarTweetsYRetweetsCorrectamente)
{
    std::ifstream archivo_tweets("retweets_de_prueba.txt");

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

    tweets[0]->asignarNuevoId();
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(tweets[0]);

    modelo::Tweet * tweet_retweeteado = new modelo::Tweet();
    tweet_retweeteado->setId(tweets[0]->getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(tweet_retweeteado);

    // datos tweet
    unsigned long long int id_parseado_tweet_1 = tweet_retweeteado->getIdTweet();
    std::string texto_parseado_tweet_1 = tweet_retweeteado->getTexto();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_tweet_1 = tweet_retweeteado->getFechaCreacion();
    unsigned long long int id_usuario_parseado_tweet_1 = tweet_retweeteado->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_tweet_1 = tweet_retweeteado->getHashtags().size();

    unsigned long long int id_correcto_tweet_1 = 958491763248893952;
    std::string texto_correcto_tweet_1 = "#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @CFKArgentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional  \nhttps://t.co/ptle5JWGte https://t.co/rM23gXjjqg";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_tweet_1(31, 1, 2018);
    unsigned long long int id_usuario_correcto_tweet_1 = 138814032;
    unsigned int tamanio_vector_hashtags_correcto_tweet_1 = 1;

    // datos retweet
    unsigned long long int id_parseado_retweet_1 = tweet_retweeteado->getTweetRetweeteado()->getIdTweet();
    std::string texto_parseado_retweet_1 = tweet_retweeteado->getTweetRetweeteado()->getTexto();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_retweet_1 = tweet_retweeteado->getTweetRetweeteado()->getFechaCreacion();
    unsigned long long int id_usuario_parseado_retweet_1 = tweet_retweeteado->getTweetRetweeteado()->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_retweet_1 = tweet_retweeteado->getTweetRetweeteado()->getHashtags().size();

    unsigned long long int id_correcto_retweet_1 = 958483263634444292;
    std::string texto_correcto_retweet_1 = "#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @CFKArgentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional  \nhttps://t.co/ptle5JWGte https://t.co/rM23gXjjqg";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_retweet_1(30, 1, 2018);
    unsigned long long int id_usuario_correcto_retweet_1 = 884164880114343937;
    unsigned int tamanio_vector_hashtags_correcto_retweet_1 = 1;

    for (std::vector<modelo::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
    {
        delete *it;
    }

    delete tweet_retweeteado;

    ASSERT_EQ(id_correcto_tweet_1, id_parseado_tweet_1);
    ASSERT_STREQ(texto_correcto_tweet_1.c_str(), texto_parseado_tweet_1.c_str());
    ASSERT_EQ(true, fecha_de_creacion_correcta_tweet_1 == fecha_de_creacion_parseada_tweet_1);
    ASSERT_EQ(id_usuario_correcto_tweet_1, id_usuario_parseado_tweet_1);
    ASSERT_EQ(tamanio_vector_hashtags_correcto_tweet_1, tamanio_vector_hashtags_parseado_tweet_1);

    ASSERT_EQ(id_correcto_retweet_1, id_parseado_retweet_1);
    ASSERT_STREQ(texto_correcto_retweet_1.c_str(), texto_parseado_retweet_1.c_str());
    ASSERT_EQ(true, fecha_de_creacion_correcta_retweet_1 == fecha_de_creacion_parseada_retweet_1);
    ASSERT_EQ(id_usuario_correcto_retweet_1, id_usuario_parseado_retweet_1);
    ASSERT_EQ(tamanio_vector_hashtags_correcto_retweet_1, tamanio_vector_hashtags_parseado_retweet_1);
}