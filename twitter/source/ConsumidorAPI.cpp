#include <twitter/include/ConsumidorAPI.h>

// protocolos
#include <protocolos/include/OAuth2.h>

using namespace scraping::twitter;
using namespace herramientas;

ConsumidorAPI::ConsumidorAPI(std::string clave_publica, std::string clave_privada) :
    cliente_twitter("https://api.twitter.com"), consumidor_oauth2(clave_publica, clave_privada)
{
}

ConsumidorAPI::~ConsumidorAPI()
{
}

bool ConsumidorAPI::obtenerTokenDeAcceso()
{
    return protocolos::OAuth2::solicitarTokenAcceso(&this->consumidor_oauth2, this->cliente_twitter.getURI());
}

herramientas::cpprest::HTTPRespuesta * ConsumidorAPI::realizarSolicitud(cpprest::HTTPSolicitud * solicitud)
{
    std::string header_token_acceso = "Bearer " + this->consumidor_oauth2.getTokenAcceso();

    solicitud->agregarEncabezado("Authorization", header_token_acceso);

    return this->cliente_twitter.solicitar(solicitud);
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS