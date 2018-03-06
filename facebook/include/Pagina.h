#pragma once

// stl
#include <string>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping
{
namespace facebook
{
namespace modelo
{

class Pagina : public scraping::extraccion::Medio
{
public:
    Pagina(std::string nombre = "");
    virtual ~Pagina();

    // GETTERS

    std::string getNombre();

    herramientas::utiles::Fecha getFechaUltimaPublicacionAnalizada();

    // getters de Medio

    virtual std::string getGrupoMedio();

    // SETTERS

    void setNombre(std::string nombre);

    void setFechaUltimaPublicacionAnalizada(herramientas::utiles::Fecha fecha_ultima_publicacion_analizada);

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

    herramientas::utiles::Fecha fecha_ultima_publicacion_analizada;
};

};
};
};


