#pragma once

// twitter
#include <twitter/include/ConsumidorAPI.h>
#include <twitter/include/Cuenta.h>
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

    // se almacena memoria para los tweets pero no se libera, entonces los tweets deben ser ELIMINADOS luego de ser usados.
    std::vector<Tweet*> leerUltimosTweets(Cuenta * cuenta, unsigned int cantidad_de_tweets = 15);

private:

    scraping::twitter::ConsumidorAPI * consumidor_api;
};

};
};
};


