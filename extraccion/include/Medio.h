#pragma once

// stl
#include <string>
#include <vector>

// utiles
#include <utiles/include/GestorIDs.h>
#include <utiles/include/IContieneJson.h>
#include <utiles/include/IHashable.h>

// scraping
#include <scraping/include/IAlmacenable.h>

// extraccion
#include <extraccion/include/Contenido.h>

namespace scraping
{

namespace extraccion
{

class Medio : public IAlmacenable, public herramientas::utiles::IContieneJson, public herramientas::utiles::IHashable
{
public:
    Medio(herramientas::utiles::Json * json = NULL);
    virtual ~Medio();

    // GETTERS

    std::vector<unsigned long long int> getIDsContenidosAnalizados();

    std::vector<unsigned long long int> getIDsContenidosNoAnalizados();

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    // METODOS

    virtual void agregarContenidoParaAnalizar(Contenido* contenido);

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS

private:

    static herramientas::utiles::GestorIDs gestor_ids_medios;

    // ATRIBUTOS

    std::vector<unsigned long long int> ids_contenidos_analizados;

    std::vector<unsigned long long int> ids_contenidos_no_analizados;
};

};
};

