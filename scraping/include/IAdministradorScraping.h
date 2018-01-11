#pragma once

// stl
#include <vector>

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

	static bool administradorIniciado();

	// GETTERS

	static IAdministradorScraping* getInstancia();

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
    void almacenarIDActual();

protected:
    // ATRIBUTOS

    almacenamiento::IAdministradorAlmacenamiento* admin_almacenamiento;

private:
	// ATRIBUTOS

	static IAdministradorScraping* administrador;
    
};

template<typename GRUPO>
bool IAdministradorScraping::recuperarGrupo(std::string prefijo_grupo, std::vector<GRUPO*>* entidades_recuperadas)
{
    std::vector<almacenamiento::IAlmacenableClaveValor*> grupo;

    this->admin_almacenamiento->recuperarGrupo(prefijo_grupo, grupo);

    GRUPO* entidad = NULL;
    for (std::vector<almacenamiento::IAlmacenableClaveValor*>::iterator it = grupo.begin(); it != grupo.end(); it++)
    {
        entidad = new GRUPO();
        unsigned long long int id = std::stoull((*it)->getClave());
        entidad->setId(new scraping::ID(id));

        this->recuperar(entidad);

        entidades_recuperadas->push_back(entidad);

        delete *it;
    }
    grupo.clear();

    return true;
};


template<typename GRUPO>
unsigned long long int IAdministradorScraping::recuperarIDActual()
{
    std::string clave = GRUPO::claveIDActual();
    std::string grupo = ConfiguracionScraping::prefijoConfiguracion();

    almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);

    bool retorno = almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_a_recuperar);

    std::string string_id_actual = clave_valor_a_recuperar->getValor();

    unsigned long long int id_actual = 0;
    if (false == string_id_actual.empty())
    {
        id_actual = std::stoull(string_id_actual);
    }

    GRUPO::getGestorIDs()->setIdActual(id_actual);

    delete clave_valor_a_recuperar;

    return id_actual;
}

template<typename GRUPO>
void IAdministradorScraping::almacenarIDActual()
{
    std::string clave = GRUPO::getClaveIDActual();
    std::string grupo = ConfiguracionScraping::prefijoConfiguracion();
    std::string valor = std::to_string(GRUPO::getGestorIDs()->getIdActual());

    almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);

    bool retorno = almacenamiento::IAdministradorAlmacenamiento::getInstancia()->modificar(clave_valor_a_recuperar);

    delete clave_valor_a_recuperar;
}

};
