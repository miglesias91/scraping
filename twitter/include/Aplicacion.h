#pragma once

// twitter
#include <twitter/include/ConsumidorAPI.h>
#include <twitter/include/Usuario.h>
#include <twitter/include/Tweet.h>

namespace scraping
{
namespace twitter
{
namespace modelo
{

class Aplicacion
{
public:
    Aplicacion(scraping::twitter::ConsumidorAPI * consumidor_api = NULL);
    virtual ~Aplicacion();

    // GETTERS

    // SETTERS

    // METODOS

    std::vector<Tweet> leerUltimosTweets(Usuario * usuario, unsigned int cantidad_de_tweets = 5);

private:

    scraping::twitter::ConsumidorAPI * consumidor_api;
};

};
};
};


