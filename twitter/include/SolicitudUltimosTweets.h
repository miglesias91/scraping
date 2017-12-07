#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/HTTPSolicitud.h>

// twitter
#include <twitter/include/Usuario.h>

namespace scraping
{
namespace twitter
{
namespace comunicacion
{

class SolicitudUltimosTweets : public herramientas::cpprest::HTTPSolicitud
{
public:
    SolicitudUltimosTweets(scraping::twitter::modelo::Usuario * usuario, unsigned int cantidad_de_tweets);
    virtual ~SolicitudUltimosTweets();
};

};
};
};


