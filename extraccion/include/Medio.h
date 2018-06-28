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
    Medio(const std::string & prefijo_grupo = "", herramientas::utiles::Json * json = NULL);
    virtual ~Medio();

    // GETTERS
    virtual bool ids_para_depurar(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa);
    virtual bool ids_para_depurar(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares);
    virtual bool ids_para_depurar(std::vector<uintmax_t> * vector);

    virtual bool ids_para_analizar(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa);
    virtual bool ids_para_analizar(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares);
    virtual bool ids_para_analizar(std::vector<uintmax_t> * vector);

    virtual bool ids_para_preparar(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa);
    virtual bool ids_para_preparar(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares);
    virtual bool ids_para_preparar(std::vector<uintmax_t> * vector);

    virtual bool ids_historicos(std::unordered_map<std::string, std::vector<uintmax_t>> * mapa);
    virtual bool ids_historicos(std::vector<std::pair<std::string, std::vector<uintmax_t>>> * pares);
    virtual bool ids_historicos(std::vector<uintmax_t> * vector);

    //std::unordered_map<std::string, std::vector<uintmax_t>> mapa_ids_para_depurar();

    //std::unordered_map<std::string, std::vector<uintmax_t>> mapa_ids_para_analizar();

    //std::unordered_map<std::string, std::vector<uintmax_t>> mapa_ids_para_preparar();

    //std::unordered_map<std::string, std::vector<uintmax_t>> mapa_ids_historias();

    //std::vector<std::pair<std::string, std::vector<uintmax_t>>> pares_ids_para_depurar();

    //std::vector<std::pair<std::string, std::vector<uintmax_t>>> pares_ids_para_analizar();

    //std::vector<std::pair<std::string, std::vector<uintmax_t>>> pares_ids_para_preparar();

    //std::vector<uintmax_t> ids_para_depurar();

    //std::vector<uintmax_t> ids_para_analizar();

    //std::vector<uintmax_t> ids_para_preparar();

    herramientas::utiles::Fecha getFechaContenidoHistoricoMasReciente();

    herramientas::utiles::Fecha getFechaContenidoHistoricoMasAntiguo();

    uintmax_t getCantidadDeContenidosHistoricos();

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();
    
    virtual std::string getGrupoMedio() = 0;

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    virtual void set_ids_para_depurar(const std::unordered_map<std::string, std::vector<uintmax_t>> & mapa);
    virtual void set_ids_para_analizar(const std::unordered_map<std::string, std::vector<uintmax_t>> & mapa);
    virtual void set_ids_para_preparar(const std::unordered_map<std::string, std::vector<uintmax_t>> & mapa);
    virtual void set_ids_historicos(const std::unordered_map<std::string, std::vector<uintmax_t>> & mapa);

    virtual bool contenido_depurado(Contenido* contenido);
    virtual bool contenido_analizado(Contenido* contenido);
    virtual bool contenido_preparado(Contenido* contenido);

    //void setMapaIDsContenidosParaDepurar(std::unordered_map<std::string, std::vector<uintmax_t>> mapa);

    //void setMapaIDsContenidosParaAnalizar(std::unordered_map<std::string, std::vector<uintmax_t>> mapa);

    //void setMapaIDsContenidosParaPreparar(std::unordered_map<std::string, std::vector<uintmax_t>> mapa);

    //void setMapaIDsContenidosHistoricos(std::unordered_map<std::string, std::vector<uintmax_t>> mapa);

    //virtual bool setearContenidoComoDepurado(Contenido* contenido);

    //virtual bool setearContenidoComoAnalizado(Contenido* contenido);

    //virtual bool setearContenidoComoHistorico(Contenido* contenido);

    // METODOS

    virtual void nuevo_contenido(Contenido* contenido);

    virtual Medio * clonar() = 0;

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS

private:

    static herramientas::utiles::GestorIDs gestor_ids_medios;

    // ATRIBUTOS

    std::unordered_map<std::string, std::vector<uintmax_t>> mapa_ids_contenidos_para_depurar;

    std::unordered_map<std::string, std::vector<uintmax_t>> mapa_ids_contenidos_para_analizar;
    
    std::unordered_map<std::string,std::vector<uintmax_t>> mapa_ids_contenidos_para_preparar;

    std::unordered_map<std::string, std::vector<uintmax_t>> mapa_ids_contenidos_historicos;

    std::string prefijo_grupo;
};

};
};

