#pragma once

// stl
#include <string>

// utiles
#include <utiles/include/GestorIDs.h>
#include <utiles/include/IContieneJson.h>
#include <utiles/include/Fecha.h>

// scraping
#include <scraping/include/IAlmacenable.h>

namespace scraping
{

namespace extraccion
{

class Contenido : public IAlmacenable, public herramientas::utiles::IContieneJson
{
public:
    Contenido(const std::string & titulo, const std::string & texto, const std::string & categoria, const herramientas::utiles::Fecha & fecha);
    Contenido(herramientas::utiles::Json * json = nullptr);
    virtual ~Contenido();

    // GETTERS

    virtual std::string getTitulo() const;
    virtual std::string getTexto() const;
    virtual std::string getCategoria() const;
    virtual herramientas::utiles::Fecha getFecha() const;

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    virtual void setTitulo(const std::string & titulo);
    virtual void setTexto(const std::string & texto);
    virtual void setCategoria(const std::string & categoria);
    virtual void setFecha(const herramientas::utiles::Fecha & fecha);

    // METODOS

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

private:

    static herramientas::utiles::GestorIDs gestor_ids_contenidos;

    // ATRIBUTOS

    std::string titulo, texto, categoria;
    herramientas::utiles::Fecha fecha;
};

};
};

