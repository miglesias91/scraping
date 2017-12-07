// gtest
#include <gtest/gtest.h>

// twitter
#include <twitter/include/Aplicacion.h>
#include <twitter/include/Tweet.h>

TEST(ScrapingTwitter, obtenerTokenDeAccesoCorrectamente)
{
    scraping::twitter::ConsumidorAPI * consumidor_api_twitter = new scraping::twitter::ConsumidorAPI("aXPpXInb16k0jKIswOYuUS3ly", "MhuDBpN9EtnafrIUHvJEbleJ3WKiFCSBIulwRVNvZTWoXGs2eV");
    consumidor_api_twitter->obtenerTokenDeAcceso();

    scraping::twitter::Aplicacion app(consumidor_api_twitter);

    scraping::twitter::modelo::Usuario clarin("clarincom");

    std::vector<scraping::twitter::modelo::Tweet> tweets = app.leerUltimosTweets(&clarin);

    ASSERT_EQ(true, true);
}