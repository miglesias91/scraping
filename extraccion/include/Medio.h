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

    std::unordered_map<std::string, std::vector<unsigned long long int>> getMapaIDsContenidosAnalizados();

    std::unordered_map<std::string, std::vector<unsigned long long int>> getMapaIDsContenidosNoAnalizados();

    std::unordered_map<std::string, std::vector<unsigned long long int>> getMapaIDsContenidosHistoricos();

    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> getParesIDsContenidosAnalizados();

    std::vector<std::pair<std::string, std::vector<unsigned long long int>>> getParesIDsContenidosNoAnalizados();

    std::vector<unsigned long long int> getIDsContenidosAnalizados();

    std::vector<unsigned long long int> getIDsContenidosNoAnalizados();

    herramientas::utiles::Fecha getFechaContenidoHistoricoMasReciente();

    herramientas::utiles::Fecha getFechaContenidoHistoricoMasAntiguo();

    unsigned long long int getCantidadDeContenidosHistoricos();

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();
    
    virtual std::string getGrupoMedio() = 0;

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    void setMapaIDsContenidosAnalizados(std::unordered_map<std::string, std::vector<unsigned long long int>> mapa);

    void setMapaIDsContenidosNoAnalizados(std::unordered_map<std::string, std::vector<unsigned long long int>> mapa);

    void setMapaIDsContenidosHistoricos(std::unordered_map<std::string, std::vector<unsigned long long int>> mapa);

    virtual bool setearContenidoComoAnalizado(Contenido* contenido);

    virtual bool setearContenidoComoHistorico(Contenido* contenido);

    // METODOS

    virtual void agregarContenidoParaAnalizar(Contenido* contenido);

    virtual Medio * clonar() = 0;

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS

private:

    static herramientas::utiles::GestorIDs gestor_ids_medios;

    // ATRIBUTOS

    std::unordered_map<std::string, std::vector<unsigned long long int>> mapa_ids_contenidos_no_analizados;
    
    std::unordered_map<std::string,std::vector<unsigned long long int>> mapa_ids_contenidos_analizados;

    std::unordered_map<std::string, std::vector<unsigned long long int>> mapa_ids_contenidos_historicos;

};

};
};

