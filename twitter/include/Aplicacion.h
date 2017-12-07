#pragma once

// twitter
#include <twitter/include/ConsumidorAPI.h>
#include <twitter/include/Usuario.h>
#include <twitter/include/Tweet.h>

namespace scraping
{
namespace twitter
{
        
class Aplicacion
{
public:
    Aplicacion(ConsumidorAPI * consumidor_api = NULL);
    virtual ~Aplicacion();

    // GETTERS

    // SETTERS

    // METODOS

    std::vector<scraping::twitter::modelo::Tweet> leerUltimosTweets(scraping::twitter::modelo::Usuario * usuario, unsigned int cantidad_de_tweets = 5);

private:

    ConsumidorAPI * consumidor_api;
};

};
};


