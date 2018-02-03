#include <scraping/include/AdministradorScrapingLocal.h>

using namespace scraping;

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>

// extraccion
#include <extraccion/include/Medio.h>
#include <extraccion/include/Contenido.h>

AdministradorScrapingLocal::AdministradorScrapingLocal() : IAdministradorScraping()
{
	//almacenamiento::IAdministradorAlmacenamiento::iniciar(ConfiguracionScraping::pathConfiguracion());

 //   this->admin_almacenamiento = almacenamiento::IAdministradorAlmacenamiento::getInstancia();
}

AdministradorScrapingLocal::~AdministradorScrapingLocal()
{
	almacenamiento::IAdministradorAlmacenamiento::liberar(this->handler_almacenamiento);
}

bool AdministradorScrapingLocal::abrirBD()
{
	bool retorno = this->admin_almacenamiento->abrir();

	return retorno;
}

bool AdministradorScrapingLocal::cerrarBD()
{
    IAdministradorScraping::almacenarIDActual<extraccion::Medio>();
    IAdministradorScraping::almacenarIDActual<extraccion::Contenido>();

	bool retorno = this->admin_almacenamiento->cerrar();

	return retorno;
}

bool AdministradorScrapingLocal::borrarBD()
{
    return this->admin_almacenamiento->borrar();
}

bool AdministradorScrapingLocal::almacenar(scraping::IAlmacenable * entidad)
{
	std::string clave = entidad->getId()->string();
	std::string grupo = entidad->getGrupo();
	std::string valor = entidad->getValorAlmacenable();

	almacenamiento::IAlmacenableClaveValor* entidad_a_almacenar = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);

	bool retorno = this->admin_almacenamiento->almacenar(entidad_a_almacenar);

	delete entidad_a_almacenar;

	return retorno;
}

bool AdministradorScrapingLocal::almacenar(std::vector<scraping::IAlmacenable*> entidades)
{
    scraping::IAlmacenable* entidad = NULL;
    bool retorno = true;

    for (std::vector<scraping::IAlmacenable*>::iterator it = entidades.begin(); it != entidades.end(); it++)
    {
        entidad = *it;
        std::string clave = entidad->getId()->string();
        std::string grupo = entidad->getGrupo();
        std::string valor = entidad->getValorAlmacenable();

        almacenamiento::IAlmacenableClaveValor* entidad_a_almacenar = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);

        retorno = this->admin_almacenamiento->almacenar(entidad_a_almacenar);
        if (false == retorno)
        {
            delete entidad_a_almacenar;
            break;
        }

        delete entidad_a_almacenar;
    }

    return retorno;
}

bool AdministradorScrapingLocal::recuperar(scraping::IAlmacenable * entidad)
{
	std::string clave = entidad->getId()->string();
	std::string grupo = entidad->getGrupo();

	almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);

	bool existe_valor = this->admin_almacenamiento->recuperar(clave_valor_a_recuperar);

    if (existe_valor)
    {
        entidad->parsearValorAlmacenable(clave_valor_a_recuperar->getValor());
    }

	delete clave_valor_a_recuperar;

	return existe_valor;
}

bool AdministradorScrapingLocal::eliminar(scraping::IAlmacenable * entidad)
{
    std::string clave = entidad->getId()->string();
    std::string grupo = entidad->getGrupo();

    almacenamiento::IAlmacenableClaveValor* entidad_a_eliminar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);

    bool retorno = this->admin_almacenamiento->eliminar(entidad_a_eliminar);

    delete entidad_a_eliminar;

    return retorno;
}

bool AdministradorScrapingLocal::eliminar(std::vector<scraping::IAlmacenable*> entidades)
{
    scraping::IAlmacenable* entidad = NULL;
    bool retorno = true;

    for (std::vector<scraping::IAlmacenable*>::iterator it = entidades.begin(); it != entidades.end(); it++)
    {
        entidad = *it;
        std::string clave = entidad->getId()->string();
        std::string grupo = entidad->getGrupo();

        almacenamiento::IAlmacenableClaveValor* entidad_a_eliminar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);

        retorno = this->admin_almacenamiento->eliminar(entidad_a_eliminar);
        if (false == retorno)
        {
            delete entidad_a_eliminar;
            break;
        }

        delete entidad_a_eliminar;
    }

    return retorno;
}

bool AdministradorScrapingLocal::modificar(scraping::IAlmacenable * entidad)
{
    std::string clave = entidad->getId()->string();
    std::string grupo = entidad->getGrupo();
    std::string valor = entidad->getValorAlmacenable();

    almacenamiento::IAlmacenableClaveValor* entidad_a_modificar = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);

    bool retorno = this->admin_almacenamiento->almacenar(entidad_a_modificar);

    delete entidad_a_modificar;

    return retorno;
}

bool AdministradorScrapingLocal::modificar(std::vector<scraping::IAlmacenable*> entidades)
{
    scraping::IAlmacenable* entidad = NULL;
    bool retorno = true;

    for (std::vector<scraping::IAlmacenable*>::iterator it = entidades.begin(); it != entidades.end(); it++)
    {
        entidad = *it;
        std::string clave = entidad->getId()->string();
        std::string grupo = entidad->getGrupo();
        std::string valor = entidad->getValorAlmacenable();

        almacenamiento::IAlmacenableClaveValor* entidad_a_modificar = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);

        retorno = this->admin_almacenamiento->modificar(entidad_a_modificar);
        if (false == retorno)
        {
            delete entidad_a_modificar;
            break;
        }

        delete entidad_a_modificar;
    }

    return retorno;
}