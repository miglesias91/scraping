#include <scraping/include/AdministradorScrapingLocal.h>

using namespace scraping;

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/Logger.h>

// extraccion
#include <extraccion/include/Medio.h>
#include <extraccion/include/Contenido.h>

AdministradorScrapingLocal::AdministradorScrapingLocal() : IAdministradorScraping()
{
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
    this->almacenarIDActual<extraccion::Medio>();
    this->almacenarIDActual<extraccion::Contenido>();

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

    if (retorno)
    {
        Logger::info("almacenar{ grupo: '" + grupo + "' - clave: '" + clave + "' }");
    }
    else
    {
        Logger::info("almacenar{ grupo: '" + grupo + "' - clave: '" + clave + "' - NO SE ALMACENO NINGUN VALOR }");
    }

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
            Logger::info("almacenar_vector{ grupo: '" + grupo + "' - clave: '" + clave + "' - NO SE PUDO ALMACENAR }");

            delete entidad_a_almacenar;
            break;
        }

        Logger::info("almacenar_vector{ grupo: '" + grupo + "' - clave: '" + clave + "' }");

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
        Logger::info("recuperar{ grupo: '" + grupo + "' - clave: '" + clave + "' }");
        entidad->parsearValorAlmacenable(clave_valor_a_recuperar->getValor());
    }
    else
    {
        Logger::info("recuperar{ grupo: '" + grupo + "' - clave: '" + clave + "' - NO SE RECUPERO NINGUN VALOR }");
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

    if (retorno)
    {
        Logger::info("eliminar{ grupo: '" + grupo + "' - clave: '" + clave + "' }");
    }
    else
    {
        Logger::info("eliminar{ grupo: '" + grupo + "' - clave: '" + clave + "' - NO SE ELIMINO NINGUN VALOR }");
    }

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
            Logger::info("eliminar_vector{ grupo: '" + grupo + "' - clave: '" + clave + "' - NO SE ELIMINO NINGUN VALOR }");
            delete entidad_a_eliminar;
            break;
        }

        Logger::info("eliminar_vector{ grupo: '" + grupo + "' - clave: '" + clave + "' }");

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

    if (retorno)
    {
        Logger::info("modificar{ grupo: '" + grupo + "' - clave: '" + clave + "' }");
    }
    else
    {
        Logger::info("modificar{ grupo: '" + grupo + "' - clave: '" + clave + "' - NO SE MODIFICO NINGUN VALOR }");
    }

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
            Logger::info("modificar_vector{ grupo: '" + grupo + "' - clave: '" + clave + "' - NO SE MODIFICO NINGUN VALOR }");
            delete entidad_a_modificar;
            break;
        }

        Logger::info("modificar_vector{ grupo: '" + grupo + "' - clave: '" + clave + "' }");

        delete entidad_a_modificar;
    }

    return retorno;
}