#pragma once

// stl
#include <string>

// utiles
#include  <utiles/include/GestorIDs.h>

// scraping
#include <scraping/include/IAlmacenable.h>

namespace scraping
{

namespace extraccion
{

class Contenido : public IAlmacenable
{
public:
    Contenido();
    virtual ~Contenido();

    // GETTERS

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    // METODOS

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS

private:

    static herramientas::utiles::GestorIDs gestor_ids_contenidos;
};

};
};

