#pragma once

// herramientas
#include <utiles/include/Fecha.h>

// twitter
#include <facebook/include/ConsumidorAPI.h>
#include <facebook/include/Pagina.h>
#include <facebook/include/Publicacion.h>

namespace scraping
{
namespace facebook
{
namespace modelo
{

class Aplicacion
{
public:
    Aplicacion(scraping::facebook::ConsumidorAPI * consumidor_api = NULL);
    virtual ~Aplicacion();

    // GETTERS

    // SETTERS

    // METODOS

    // se almacena memoria para las publicaciones pero no se libera, entonces deben ser ELIMINADAS luego de ser usadas.
    std::vector<Publicacion*> leerUltimasPublicaciones(Pagina * cuenta, unsigned int cantidad_de_publicaciones = 100);

    // se almacena memoria para las publicaciones pero no se libera, entonces deben ser ELIMINADAS luego de ser usadas.
    std::vector<Publicacion*> leerPublicaciones(Pagina * cuenta, herramientas::utiles::Fecha desde, herramientas::utiles::Fecha hasta, unsigned int cantidad_de_publicaciones = 100);

private:

    scraping::facebook::ConsumidorAPI * consumidor_api;
};

};
};
};


