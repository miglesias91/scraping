#pragma once

// stl
#include <string>

// utiles
#include <utiles/include/GestorIDs.h>
#include <utiles/include/IContieneJson.h>

// scraping
#include <scraping/include/IAlmacenable.h>

namespace scraping
{

namespace extraccion
{

class Contenido : public IAlmacenable, public herramientas::utiles::IContieneJson
{
public:
    Contenido(herramientas::utiles::Json * json = NULL);
    virtual ~Contenido();

    // GETTERS

    virtual std::string getTexto();

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    virtual void setTexto(std::string texto);

    // METODOS

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS

private:

    static herramientas::utiles::GestorIDs gestor_ids_contenidos;

    // ATRIBUTOS

    std::string texto;
};

};
};

