#pragma once

// stl
#include <string>
#include <vector>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAlmacenable.h>

// analisis
#include <analisis/include/IAnalizable.h>

namespace scraping
{
namespace depuracion
{

class ContenidoDepurado : public IAlmacenable
{
public:
    ContenidoDepurado();
    ContenidoDepurado(std::vector<std::string> bolsa_de_palabras_depurada);
    virtual ~ContenidoDepurado();

    // GETTERS

    std::vector<std::string> getBolsaDePalabras();

    // SETTERS

    void bolsa_de_palabras(const std::vector<std::string> & bolsa_de_palabras_depurada);

    // METODOS

    // de IAlmacenable
    virtual std::string getValorAlmacenable();

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS

    bool vacio();

private:

    std::vector<std::string> bolsa_de_palabras_depurada;
};

};
};


