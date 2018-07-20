#pragma once

// stl
#include <string>
#include <vector>
#include <mutex>
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
    Medio(const std::string & prefijo_grupo = "", herramientas::utiles::Json * json = nullptr);
    virtual ~Medio();

    // GETTERS
    virtual uintmax_t tamanio() const;
    virtual void tamanio(const uintmax_t& tamanio_total);

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

    herramientas::utiles::Fecha getFechaContenidoHistoricoMasReciente() const;

    herramientas::utiles::Fecha getFechaContenidoHistoricoMasAntiguo() const;

    uintmax_t getCantidadDeContenidosHistoricos() const;

    static std::string getClaveIDActual();

    static herramientas::utiles::GestorIDs * getGestorIDs();
    
    virtual std::string getGrupoMedio() = 0;
    virtual std::string etiqueta() const = 0;

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

    virtual bool contenido_depurado(const std::string & fecha_aaaammdd, const uintmax_t & id_contenido);
    virtual bool contenido_analizado(const std::string & fecha_aaaammdd, const uintmax_t & id_contenido);
    virtual bool contenido_preparado(const std::string & fecha_aaaammdd, const uintmax_t & id_contenido);
    virtual bool contenidos_preparados(const std::string & fecha_aaaammdd, const std::vector<uintmax_t> & ids_contenidos);

    // METODOS

    virtual void nuevo(Contenido* contenido);

    virtual Medio * clonar() = 0;

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS
protected:
    static std::mutex mutex_modificacion_id_contenido;

    uintmax_t tamanio_total;

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

