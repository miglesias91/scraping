#pragma once

// stl
#include <string>
#include <vector>
#include <unordered_map>

// utiles
#include <utiles/include/GestorIDs.h>
#include <utiles/include/IContieneJson.h>
#include <utiles/include/IHashable.h>
#include <utiles/include/Fecha.h>

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

    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> getMapaIDsContenidosAnalizados();

    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> getMapaIDsContenidosNoAnalizados();

    std::vector<unsigned long long int> getIDsContenidosAnalizados();

    std::vector<unsigned long long int> getIDsContenidosNoAnalizados();

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    virtual bool setearContenidoComoAnalizado(Contenido* contenido);

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

    std::unordered_map<std::string,std::vector<unsigned long long int>> mapa_ids_contenidos_analizados;

    std::unordered_map<std::string, std::vector<unsigned long long int>> mapa_ids_contenidos_no_analizados;
};

};
};

