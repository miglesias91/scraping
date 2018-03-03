#pragma once

// stl
#include <vector>

// log
#include <log/include/AdministradorLog.h>

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

// modelo
#include <scraping/include/IAlmacenable.h>

namespace scraping
{

class IAdministradorScraping
{
public:
    IAdministradorScraping();
    virtual ~IAdministradorScraping();

    static void iniciar(std::string path_configuracion);

    static void liberar();

    static void crearAdministradorScrapingLocal();

    static void crearAdministradorScrapingDistribuido();

    static bool administradorInfoIniciado();

    static bool administradorResultadosAnalisisDiarioIniciado();

    // GETTERS

    static herramientas::log::Logger * log;

    static IAdministradorScraping* getInstanciaAdminInfo();

    static IAdministradorScraping* getInstanciaAdminResultadosAnalisisDiario();

    // SETTERS

    // METODOS

    virtual bool abrirBD() = 0;

    virtual bool cerrarBD() = 0;

    virtual bool borrarBD() = 0;

    virtual bool almacenar(scraping::IAlmacenable* almacenable) = 0;

    virtual bool almacenar(std::vector<scraping::IAlmacenable*> almacenables) = 0;

    virtual bool recuperar(scraping::IAlmacenable* almacenable) = 0;

    virtual bool eliminar(scraping::IAlmacenable * almacenable) = 0;

    virtual bool eliminar(std::vector<scraping::IAlmacenable*> almacenables) = 0;

    virtual bool modificar(scraping::IAlmacenable * almacenable) = 0;

    virtual bool modificar(std::vector<scraping::IAlmacenable*> almacenables) = 0;

    template <typename ENTIDAD>
    bool recuperarGrupo(std::string prefijo_grupo, std::vector<ENTIDAD*>* entidades_recuperadas);

    template<typename GRUPO>
    unsigned long long int recuperarIDActual();

    template<typename GRUPO>
    bool almacenarIDActual();

    virtual void recuperarIDsActuales();

    virtual void almacenarIDsActuales();

protected:

    // METODOS PROTEGIDOS

    void iniciarDB(std::string path_config_db);

    // ATRIBUTOS

    almacenamiento::IAdministradorAlmacenamiento* admin_almacenamiento;

    unsigned long long int handler_almacenamiento;

private:
	// ATRIBUTOS

    static IAdministradorScraping * administrador_info;

    static IAdministradorScraping * administrador_resultados_analisis_diario;

    
};

template<typename GRUPO>
bool IAdministradorScraping::recuperarGrupo(std::string prefijo_grupo, std::vector<GRUPO*>* entidades_recuperadas)
{
    std::vector<almacenamiento::IAlmacenableClaveValor*> grupo;

    this->admin_almacenamiento->recuperarGrupo(prefijo_grupo, grupo);

    log->debug("recuperarGrupo: " + std::to_string(grupo.size()) + " entidades recuperadas.");

    GRUPO* entidad = NULL;
    for (std::vector<almacenamiento::IAlmacenableClaveValor*>::iterator it = grupo.begin(); it != grupo.end(); it++)
    {
        entidad = new GRUPO();
        unsigned long long int id = std::stoull((*it)->getClave());
        entidad->setId(new herramientas::utiles::ID(id));

        entidad->parsearValorAlmacenable((*it)->getValor());

        entidades_recuperadas->push_back(entidad);

        delete *it;
    }
    grupo.clear();

    return true;
};


template<typename GRUPO>
unsigned long long int IAdministradorScraping::recuperarIDActual()
{
    std::string clave = GRUPO::getClaveIDActual();
    std::string grupo = ConfiguracionScraping::prefijoConfiguracion();

    almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);

    bool retorno = almacenamiento::IAdministradorAlmacenamiento::getInstancia(this->handler_almacenamiento)->recuperar(clave_valor_a_recuperar);

    std::string string_id_actual = clave_valor_a_recuperar->getValor();

    log->debug("recuperarIDActual: { clave: " + clave + " - id_actual: " + string_id_actual + ".");

    unsigned long long int id_actual = 1;
    if (false == string_id_actual.empty())
    {
        id_actual = std::stoull(string_id_actual);
    }

    GRUPO::getGestorIDs()->setIdActual(id_actual);

    delete clave_valor_a_recuperar;

    return id_actual;
}

template<typename GRUPO>
bool IAdministradorScraping::almacenarIDActual()
{
    std::string clave = GRUPO::getClaveIDActual();
    std::string grupo = ConfiguracionScraping::prefijoConfiguracion();
    std::string valor = std::to_string(GRUPO::getGestorIDs()->getIdActual());

    almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);

    bool retorno = almacenamiento::IAdministradorAlmacenamiento::getInstancia(this->handler_almacenamiento)->modificar(clave_valor_a_recuperar);

    delete clave_valor_a_recuperar;

    return retorno;
}

};

