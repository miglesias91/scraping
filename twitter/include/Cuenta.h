#pragma once

// stl
#include <string>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping
{
namespace twitter
{
namespace modelo
{

class Cuenta : public scraping::extraccion::Medio
{
public:
    Cuenta(std::string nombre = "");
    virtual ~Cuenta();

    // GETTERS

    std::string getNombre();

    unsigned long long int getIdUltimoTweetAnalizado();

    // SETTERS

    void setNombre(std::string nombre);

    void setIdUltimoTweetAnalizado(unsigned long long int id_ultimo_tweet_analizado);

    // METODOS

    // metodos de Medio

    virtual Medio * clonar();

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();
    
    // metodos de IHashable

    virtual unsigned long long int hashcode();

    // CONSULTAS

private:

    // ATRIBUTOS

    std::string nombre;

    unsigned long long int id_ultimo_tweet_analizado;
};

};
};
};


