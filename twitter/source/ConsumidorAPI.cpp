#include <twitter/include/ConsumidorAPI.h>

// protocolos
#include <protocolos/include/OAuth2.h>

using namespace scraping::twitter;

ConsumidorAPI::ConsumidorAPI(std::string clave_publica, std::string clave_privada) :
    cliente_twitter("https://api.twitter.com"), consumidor_oauth2(clave_publica, clave_privada, "https://api.twitter.com")
{
}

ConsumidorAPI::~ConsumidorAPI()
{
}

bool ConsumidorAPI::obtenerTokenDeAcceso()
{
    return herramientas::protocolos::OAuth2::solicitarTokenAcceso(&this->consumidor_oauth2);
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS