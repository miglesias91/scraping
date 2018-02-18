#pragma once

// extraccion
#include <extraccion/include/Medio.h>

// twitter
#include <twitter/include/Cuenta.h>

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

    bool recuperarTodos(std::vector<scraping::extraccion::Medio*> & medios);

    bool actualizarCuentaDeTwitter(scraping::twitter::modelo::Cuenta * cuenta_a_actualizar);

    bool recuperarCuentasDeTwitter(std::vector<scraping::twitter::modelo::Cuenta*> & cuentas_de_twitter);

    bool agregarCuentaDeTwitter(scraping::twitter::modelo::Cuenta * medio_nuevo);
    
    bool almacenarIDActualMedio();

    void recuperarIDActualMedio();

    // CONSULTAS

    template <typename MEDIO>
    bool existeMedio(std::vector<MEDIO*> & medios, scraping::extraccion::Medio * medio_a_consultar);

private:

};

template <typename MEDIO>
bool GestorMedios::existeMedio(std::vector<MEDIO*> & medios, scraping::extraccion::Medio * medio_a_consultar)
{
    for (std::vector<MEDIO*>::iterator it = medios.begin(); it != medios.end(); it++)
    {
        if ((*it)->hashcode() == medio_a_consultar->hashcode())
        {
            return true;
        }
    }
    return false;
}

};
};