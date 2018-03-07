#pragma once

// casablanca wrapper
#include <casablanca_wrapper/include/HTTPCliente.h>
#include <casablanca_wrapper/include/HTTPSolicitud.h>

// protocolos
#include <protocolos/include/OAuth2Consumidor.h>

namespace scraping
{
namespace facebook
{

class ConsumidorAPI
{
public:
    ConsumidorAPI(std::string clave_publica, std::string clave_privada);
    virtual ~ConsumidorAPI();

    // GETTERS

    herramientas::protocolos::OAuth2Consumidor getConsumidorOAuth2();

    // SETTERS

    // METODOS

    bool obtenerTokenDeAcceso();

    herramientas::cpprest::HTTPRespuesta * realizarSolicitud(herramientas::cpprest::HTTPSolicitud * solicitud);

    // CONSULTAS

private:

    // ATRIBUTOS

    herramientas::protocolos::OAuth2Consumidor consumidor_oauth2;

    herramientas::cpprest::HTTPCliente cliente_facebook;
};

};
};


