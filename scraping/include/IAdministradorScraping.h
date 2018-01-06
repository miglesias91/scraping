#pragma once

// stl
#include <vector>

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

// modelo
#include <modelo/include/IAlmacenable.h>

namespace scraping
{

class IAdministradorScraping
{
public:
    IAdministradorScraping();
    virtual ~IAdministradorScraping();

	static void iniciar(std::string path_configuracion);

	static void liberar();

	static void crearAdministradorAplicacionLocal();

	static void crearAdministradorAplicacionDistribuida();

	static bool administradorIniciado();

	// GETTERS

	static IAdministradorScraping* getInstancia();

	// SETTERS

	// METODOS

	virtual bool abrirBD() = 0;

    virtual bool cerrarBD() = 0;

    virtual bool borrarBD() = 0;

    virtual bool almacenar(visualizador::modelo::IAlmacenable* almacenable) = 0;

    virtual bool almacenar(std::vector<visualizador::modelo::IAlmacenable*> almacenables) = 0;

    virtual bool recuperar(visualizador::modelo::IAlmacenable* almacenable) = 0;

    virtual bool eliminar(visualizador::modelo::IAlmacenable * almacenable) = 0;

    virtual bool eliminar(std::vector<visualizador::modelo::IAlmacenable*> almacenables) = 0;

    virtual bool modificar(visualizador::modelo::IAlmacenable * almacenable) = 0;

    virtual bool modificar(std::vector<visualizador::modelo::IAlmacenable*> almacenables) = 0;

    // virtual bool recuperarGrupo(std::string prefijo_grupo, std::vector<visualizador::modelo::IAlmacenable*>* almacenables) = 0;

    template <class ENTIDAD>
    bool recuperarGrupo(std::string prefijo_grupo, std::vector<ENTIDAD*>* entidades_recuperadas);

	virtual unsigned long long int recuperarIDActual() = 0;

	virtual void almacenarIDActual() = 0;

protected:
    // ATRIBUTOS

    almacenamiento::IAdministradorAlmacenamiento* admin_almacenamiento;

private:
	// ATRIBUTOS

	static IAdministradorScraping* administrador;
    
};

template<typename ENTIDAD>
bool IAdministradorScraping::recuperarGrupo(std::string prefijo_grupo, std::vector<ENTIDAD*>* entidades_recuperadas)
{
    std::vector<almacenamiento::IAlmacenableClaveValor*> grupo;

    this->admin_almacenamiento->recuperarGrupo(prefijo_grupo, grupo);

    ENTIDAD* entidad = NULL;
    for (std::vector<almacenamiento::IAlmacenableClaveValor*>::iterator it = grupo.begin(); it != grupo.end(); it++)
    {
        entidad = new ENTIDAD();
        unsigned long long int id = std::stoull((*it)->getClave());
        entidad->setId(new visualizador::aplicacion::ID(id));

        this->recuperar(entidad);

        entidades_recuperadas->push_back(entidad);

        delete *it;
    }
    grupo.clear();

    return true;
};


};

