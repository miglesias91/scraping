#include <scraping/include/GestorMedios.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/Logger.h>

using namespace scraping::aplicacion;

GestorMedios::GestorMedios() : admin_info_scraping(NULL), prefijo_grupo(prefijo_grupo)
{
    this->admin_info_scraping = scraping::IAdministradorScraping::getInstanciaAdminInfo();
}

GestorMedios::~GestorMedios()
{
    for (this->medios_it = this->medios_existentes.begin(); this->medios_it != this->medios_existentes.end(); this->medios_it++)
    {
        delete (*this->medios_it);
    }
    this->medios_existentes.clear();

    for (this->medios_it = this->medios_a_almacenar.begin(); this->medios_it != this->medios_a_almacenar.end(); this->medios_it++)
    {
        delete (*this->medios_it);
    }
    this->medios_a_almacenar.clear();

    for (this->medios_it = this->medios_a_eliminar.begin(); this->medios_it != this->medios_a_eliminar.end(); this->medios_it++)
    {
        delete (*this->medios_it);
    }
    this->medios_a_eliminar.clear();
}

bool GestorMedios::guardarCambios()
{
    if (this->prefijo_grupo.empty())
    {
        // si el prefijo no fue seteado, entonces es IMPOSIBLE guardar los medios porque no se a que grupo pertenencen.
        throw - 1;
    }

    for (this->medios_it = this->medios_a_almacenar.begin(); this->medios_it != this->medios_a_almacenar.end(); this->medios_it++)
    {
        scraping::extraccion::Medio * medio_a_almacenar = *this->medios_it;
        medio_a_almacenar->setGrupo(this->prefijo_grupo);
        this->admin_info_scraping->almacenar(medio_a_almacenar);

        this->medios_existentes.push_back(*this->medios_it);
    }
    this->medios_a_almacenar.clear();

    for (this->medios_it = this->medios_a_eliminar.begin(); this->medios_it != this->medios_a_eliminar.end(); this->medios_it++)
    {
        scraping::extraccion::Medio * medio_a_eliminar = *this->medios_it;
        medio_a_eliminar->setGrupo(this->prefijo_grupo);
        this->admin_info_scraping->eliminar(medio_a_eliminar);
        delete (*this->medios_it);
    }
    this->medios_a_eliminar.clear();

    return true;
}

bool GestorMedios::existe(scraping::extraccion::Medio * medio_a_chequear)
{
    for (this->medios_it = this->medios_existentes.begin(); this->medios_it != this->medios_existentes.end(); this->medios_it++)
    {
        if ((*this->medios_it)->hashcode() == medio_a_chequear->hashcode())
        {
            return true;
        }
    }

    for (this->medios_it = this->medios_a_almacenar.begin(); this->medios_it != this->medios_a_almacenar.end(); this->medios_it++)
    {
        if ((*this->medios_it)->hashcode() == medio_a_chequear->hashcode())
        {
            return true;
        }
    }

    return false;
}

bool GestorMedios::almacenar(scraping::extraccion::Medio * medio_nuevo)
{
    // si ya existe el medio, entonces devuelvo 'false' indicando que no se agregó la nuevo medio
    // y tiro una excepcion avisando que ya existe una medio igual.
    if (this->existe(medio_nuevo))
    {
        // TODO implementar 'ExcepcionTerminoExistente'.
        // std::string mensaje("La medio '" + medio_nuevo->getEtiqueta() + "' ya existe.");
        // throw std::exception(mensaje.c_str());
        return false;
    }

    // chequeo que el medio a agregar no este en la lista de eliminados:
    // si estaba en la lista de eliminados, entonces quiere decir que esta en la bd y se queria sacar, pero ahora la queremos agregar.
    // Entonces lo que hago es sacarlo de la lista de "a eliminar" y lo vuelvo a agregar a la lista de "existentes".
    for (this->medios_it = this->medios_a_eliminar.begin(); this->medios_it != this->medios_a_eliminar.end(); this->medios_it++)
    {
        if ((*this->medios_it)->hashcode() == medio_nuevo->hashcode())
        {
            this->medios_existentes.push_back(*this->medios_it);
            this->medios_a_eliminar.erase(this->medios_it);
            return true;
        }
    }

    // si no estaba en la lista de eliminados, entonces lo agregar a la lista de 'a almacenar'.
    if (NULL == medio_nuevo->getId())
    {
        medio_nuevo->asignarNuevoId();
    }
    this->medios_a_almacenar.push_back(medio_nuevo->clonar());

    return true;
}

bool GestorMedios::eliminar(scraping::extraccion::Medio * medio_a_eliminar)
{
    // chequeo que el medio a eliminar no este en la lista de medios que se quieren almacenar.
    // en caso que SI este, entonces directamente la elimino de la lista de medios a almacenar. De esta forma evito tocar la bd.
    for (this->medios_it = this->medios_a_almacenar.begin(); this->medios_it != this->medios_a_almacenar.end(); this->medios_it++)
    {
        if ((*this->medios_it)->hashcode() == medio_a_eliminar->hashcode())
        {
            // si NO apuntan a la misma medio, entonces borro la que esta en "a almacenar"
            if (medio_a_eliminar != *this->medios_it)
            {
                delete *this->medios_it;
            }

            this->medios_a_almacenar.erase(this->medios_it);
            return true;
        }
    }

    for (this->medios_it = this->medios_existentes.begin(); this->medios_it != this->medios_existentes.end(); this->medios_it++)
    {
        if ((*this->medios_it)->hashcode() == medio_a_eliminar->hashcode())
        {
            this->medios_a_eliminar.push_back(*this->medios_it);
            this->medios_existentes.erase(this->medios_it);
            return true;
        }
    }

    return false;
}

scraping::extraccion::Medio * GestorMedios::encontrar(scraping::extraccion::Medio * medio_a_encontrar)
{
    for (this->medios_it = this->medios_existentes.begin(); this->medios_it != this->medios_existentes.end(); this->medios_it++)
    {
        if ((*this->medios_it)->hashcode() == medio_a_encontrar->hashcode())
        {
            return *this->medios_it;
        }
    }

    for (this->medios_it = this->medios_a_almacenar.begin(); this->medios_it != this->medios_a_almacenar.end(); this->medios_it++)
    {
        if ((*this->medios_it)->hashcode() == medio_a_encontrar->hashcode())
        {
            return *this->medios_it;;
        }
    }

    return NULL;
}

// METODOS VIEJOS

//bool GestorMedios::recuperarTodos(std::vector<scraping::extraccion::Medio*>& medios)
//{
//    return false;
//}

bool GestorMedios::actualizarCuentaDeTwitter(scraping::twitter::modelo::Cuenta * cuenta_a_actualizar)
{
    cuenta_a_actualizar->setGrupo(scraping::ConfiguracionScraping::prefijoTwitter());

    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->modificar(cuenta_a_actualizar);

    return false;
}

bool GestorMedios::recuperarCuentasDeTwitter(std::vector<scraping::twitter::modelo::Cuenta*> & cuentas_de_twitter)
{
    scraping::Logger::info("recuperarCuentasDeTwitter: recuperando las cuentas de twitter existentes.");

    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->recuperarGrupo<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), &cuentas_de_twitter);
}

bool GestorMedios::agregarCuentaDeTwitter(scraping::twitter::modelo::Cuenta * medio_nuevo)
{
    medio_nuevo->setGrupo(scraping::ConfiguracionScraping::prefijoTwitter());

    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->almacenar(medio_nuevo);
}

bool GestorMedios::almacenarIDActualMedio()
{
    return scraping::IAdministradorScraping::getInstanciaAdminInfo()->almacenarIDActual<scraping::extraccion::Medio>();
}

void GestorMedios::recuperarIDActualMedio()
{
    unsigned long long int id_actual_medio = IAdministradorScraping::getInstanciaAdminInfo()->recuperarIDActual<scraping::extraccion::Medio>();

    scraping::extraccion::Medio::getGestorIDs()->setIdActual(id_actual_medio);
}