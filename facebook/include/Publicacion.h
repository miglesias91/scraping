#pragma once

// herramientas
#include <utiles/include/IContieneJson.h>
#include <utiles/include/Fecha.h>

// extraccion
#include <extraccion/include/Contenido.h>

namespace scraping
{
namespace facebook
{
namespace modelo
{

class Publicacion : public scraping::extraccion::Contenido
{
public:

    Publicacion(herramientas::utiles::Json * tweet_json = NULL);
	virtual ~Publicacion();

    // GETTERS

    unsigned long long int getIdPublicacion();

    unsigned long long int getIdPagina();

    herramientas::utiles::Fecha getFechaCreacion();

    std::string getTextoPublicacion();

    // SETTERS

    void setIdPublicacion(unsigned long long int id_publicacion);

    void setIdPagina(unsigned long long int id_pagina);

    void setFechaCreacion(herramientas::utiles::Fecha fecha_creacion);

    void setTextoPublicacion(std::string texto_tweet);

    // METODOS

    // metodos de IContieneJson
    
    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

    // OPERADORES

private:

    // METODOS PRIVADOS

    herramientas::utiles::Fecha parsearFechaEnFormatoFacebook(std::string fecha_formato_facebook);

    // ATRIBUTOS

    unsigned long long int id_publicacion;

    unsigned long long int id_pagina;

    herramientas::utiles::Fecha fecha_creacion;

    // esta en formato UTF8 xq obtiene el valor del Json (rapidjson) que contiene.
    // (ir al test 'GettersYSettersCodificaciones' de 'herramientas_desarrollo' para ver como funciona.
    std::string texto_publicacion;
};

};
};
};


