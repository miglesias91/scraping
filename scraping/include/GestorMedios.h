#pragma once

// scraping
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/PrefijoDeMedioNoSeteado.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping
{
namespace aplicacion
{

class GestorMedios
{
public:
    GestorMedios();
    virtual ~GestorMedios();

    // GETTES

    // SETTER

    // METODOS

    // almacena en la base de datos en el momento.
    bool almacenar_ya(const std::vector<scraping::extraccion::Medio*> & medios_a_almacenar) const;
    // elimina de la base de datos en el momento.
    bool eliminar_ya(const std::vector<scraping::extraccion::Medio*> & medios_a_eliminar) const;

    bool actualizarMedio(scraping::extraccion::Medio * medio_a_actualizar) const;

    bool almacenarMedio(scraping::extraccion::Medio * medio_a_almacenar) const;
    
    bool almacenarIDActualMedio() const;

    void recuperarIDActualMedio() const;

    template <class MEDIO>
    std::vector<MEDIO*> gestionar(std::string prefijo_grupo);

    template <class MEDIO>
    bool recuperar(std::string prefijo_grupo, std::vector<MEDIO*> & medios_a_recuperar);

    // clona la medio devolviendo un puntero de la clase especifica de la medio.
    // Similar al metodo "clonar" de cada medio, solo que agrega el tipo de medio indicado en <ENTIDAD>.
    template <class MEDIO>
    MEDIO * clonar(scraping::extraccion::Medio* medio_a_clonar);

    // chequea que existe el termino en la lista de terminos de la ui.
    bool existe(scraping::extraccion::Medio* medio_a_chequear);

    // almacena logicamente el termino.
    bool almacenar(scraping::extraccion::Medio* medio_a_almacenar);

    // elimina logicamente el termino.
    bool eliminar(scraping::extraccion::Medio* medio_a_eliminar);

    // devuelve el puntero a la medio en caso que se encuentre en la lista de 'existentes' o de 'a almacenar'
    scraping::extraccion::Medio* encontrar(scraping::extraccion::Medio* medio_a_encontrar);

    bool guardarCambios();

    // CONSULTAS

    template <typename MEDIO>
    bool existeMedio(std::vector<MEDIO*> & medios, scraping::extraccion::Medio * medio_a_consultar);

private:

    // lista de terminos que SI ESTAN en la bd y figuran en la lista. se usa para operar logicamente.
    std::vector<scraping::extraccion::Medio*> medios_existentes;

    // lista de terminos que NO ESTAN en la bd y se quieren agregar. se usa para operar logicamente.
    std::vector<scraping::extraccion::Medio*> medios_a_almacenar;

    // lista de terminos que SI ESTAN en la bd y se quieren eliminar. se usa para operar logicamente.
    std::vector<scraping::extraccion::Medio*> medios_a_eliminar;

    std::vector<scraping::extraccion::Medio*>::iterator medios_it;

    scraping::IAdministradorScraping * admin_info_scraping;

    std::string prefijo_grupo;
};

template <class MEDIO>
std::vector<MEDIO*> GestorMedios::gestionar(std::string prefijo_grupo) {
    if (prefijo_grupo.empty()) {
        // si el prefijo no fue seteado, entonces es IMPOSIBLE guardar los medios porque no se a que grupo pertenencen.
        throw excepciones::PrefijoDeMedioNoSeteado();
    }

    this->prefijo_grupo = prefijo_grupo;

    std::vector<MEDIO*> medios_a_recuperar;

    bool valor_retorno = scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperarGrupo<MEDIO>(prefijo_grupo, &medios_a_recuperar);

    for (std::vector<MEDIO*>::iterator it = medios_a_recuperar.begin(); it != medios_a_recuperar.end(); it++) {
        this->medios_existentes.push_back(*it);
    }

    return medios_a_recuperar;
};

template <class MEDIO>
bool GestorMedios::recuperar(std::string prefijo_grupo, std::vector<MEDIO*> & medios_a_recuperar) {
    if (prefijo_grupo.empty()) {
        throw excepciones::PrefijoDeMedioNoSeteado();
    }

    return scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperarGrupo<MEDIO>(prefijo_grupo, &medios_a_recuperar);
};

template <class MEDIO>
MEDIO* GestorMedios::clonar(scraping::extraccion::Medio* medio_a_clonar) {
    scraping::extraccion::Medio* medio_clonado = medio_a_clonar->clonar();
    return static_cast<MEDIO*>(medio_clonado);
};

template <typename MEDIO>
bool GestorMedios::existeMedio(std::vector<MEDIO*> & medios, scraping::extraccion::Medio * medio_a_consultar) {
    for (std::vector<MEDIO*>::iterator it = medios.begin(); it != medios.end(); it++) {
        if ((*it)->hashcode() == medio_a_consultar->hashcode())
        {
            return true;
        }
    }
    return false;
};

};
};