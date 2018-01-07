#pragma once

// stl
#include <string>

// aplicacion
#include <utiles/include/ID.h>

namespace scraping
{

class IAlmacenable
{
public:
    IAlmacenable(std::string grupo = "");
    virtual ~IAlmacenable();

    // GETTERS

    virtual herramientas::utiles::ID * getId();

    virtual std::string getGrupo();

    virtual std::string getValorAlmacenable() = 0;

    // SETTERS

    virtual void setId(herramientas::utiles::ID* id);

    virtual void setGrupo(std::string grupo);

    // METODOS

    virtual void asignarNuevoId() = 0;

    virtual void parsearValorAlmacenable(std::string valor_almacenable) = 0;

    virtual std::string prefijoGrupo() = 0;

    static bool comparador(IAlmacenable* a, IAlmacenable* b);

private:

    // ATRIBUTOS

    herramientas::utiles::ID* id;
    std::string grupo;

};
};

