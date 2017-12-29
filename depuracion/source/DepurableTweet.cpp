#include <depuracion/include/DepurableTweet.h>

using namespace scraping::depuracion;

DepurableTweet::DepurableTweet(scraping::twitter::modelo::Tweet tweet_a_depurar) : IDepurable(), tweet_a_depurar(tweet_a_depurar)
{
}

DepurableTweet::~DepurableTweet()
{
}

std::string DepurableTweet::getTextoDepurable()
{
    return this->tweet_a_depurar.getTexto();
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS