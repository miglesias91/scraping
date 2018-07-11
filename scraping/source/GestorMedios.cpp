#include <scraping/include/GestorMedios.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/Logger.h>

using namespace scraping::aplicacion;

GestorMedios::GestorMedios() : admin_info_scraping(nullptr), prefijo_grupo(prefijo_grupo)
{
    this->admin_info_scraping = scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios();
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
    for (this->medios_it = this->medios_a_almacenar.begin(); this->medios_it != this->medios_a_almacenar.end(); this->medios_it++)
    {
        scraping::extraccion::Medio * medio_a_almacenar = *this->medios_it;
        //medio_a_almacenar->setGrupo(this->prefijo_grupo);
        this->admin_info_scraping->almacenar(medio_a_almacenar);

        this->medios_existentes.push_back(*this->medios_it);
    }
    this->medios_a_almacenar.clear();

    for (this->medios_it = this->medios_a_eliminar.begin(); this->medios_it != this->medios_a_eliminar.end(); this->medios_it++)
    {
        scraping::extraccion::Medio * medio_a_eliminar = *this->medios_it;
        //medio_a_eliminar->setGrupo(this->prefijo_grupo);
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
    if (nullptr == medio_nuevo->getId())
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

    return nullptr;
}

// METODOS VIEJOS

bool GestorMedios::almacenar(const std::vector<scraping::extraccion::Medio*>& medios_a_almacenar) const {

    std::for_each(medios_a_almacenar.begin(), medios_a_almacenar.end(),
        [=](scraping::extraccion::Medio * medio_a_almacenar) {
        this->almacenarMedio(medio_a_almacenar);
    });
    return true;
}

bool GestorMedios::actualizarMedio(scraping::extraccion::Medio * medio_a_actualizar) const
{
    medio_a_actualizar->setGrupo(medio_a_actualizar->getGrupoMedio());

    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->modificar(medio_a_actualizar);
}

bool GestorMedios::almacenarMedio(scraping::extraccion::Medio * medio_a_almacenar) const
{
    medio_a_almacenar->setGrupo(medio_a_almacenar->getGrupoMedio());

    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenar(medio_a_almacenar);
}

bool GestorMedios::almacenarIDActualMedio() const
{
    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenarIDActual<scraping::extraccion::Medio>();
}

void GestorMedios::recuperarIDActualMedio() const
{
    unsigned long long int id_actual_medio = IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperarIDActual<scraping::extraccion::Medio>();

    scraping::extraccion::Medio::getGestorIDs()->setIdActual(id_actual_medio);
}