#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/HTTPSolicitud.h>

// twitter
#include <twitter/include/Cuenta.h>

namespace scraping
{
namespace twitter
{
namespace comunicacion
{

class SolicitudUltimosTweets : public herramientas::cpprest::HTTPSolicitud
{
public:
    SolicitudUltimosTweets(scraping::twitter::modelo::Cuenta * cuenta, unsigned int cantidad_de_tweets);
    virtual ~SolicitudUltimosTweets();
};

};
};
};


