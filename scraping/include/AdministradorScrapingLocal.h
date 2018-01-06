#pragma once

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

// aplicacion
#include <scraping/include/IAdministradorScraping.h>

namespace scraping
{

class AdministradorScrapingLocal : public IAdministradorScraping
{
public:
	AdministradorScrapingLocal();
	virtual ~AdministradorScrapingLocal();

	// METODOS

	virtual bool abrirBD();

	virtual bool cerrarBD();

    virtual bool borrarBD();
    
    virtual bool almacenar(scraping::IAlmacenable* almacenable);

    virtual bool almacenar(std::vector<scraping::IAlmacenable*> almacenables);

    virtual bool recuperar(scraping::IAlmacenable* almacenable);

    virtual bool eliminar(scraping::IAlmacenable * almacenable);

    virtual bool eliminar(std::vector<scraping::IAlmacenable*> almacenables);

    virtual bool modificar(scraping::IAlmacenable * almacenable);

    virtual bool modificar(std::vector<scraping::IAlmacenable*> almacenables);

    virtual bool recuperarGrupo(std::string prefijo_grupo, std::vector<scraping::IAlmacenable*>* almacenables);

    virtual unsigned long long int recuperarIDActual();

    virtual void almacenarIDActual();

private:

};

};

