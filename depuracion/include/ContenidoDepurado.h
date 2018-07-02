#pragma once

// stl
#include <string>
#include <vector>

// utiles
#include <utiles/include/Fecha.h>

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
    ContenidoDepurado(const std::vector<std::string> & bolsa_de_palabras_depurada, const uint32_t & tamanio);
    virtual ~ContenidoDepurado();

    // GETTERS

    std::vector<std::string> getBolsaDePalabras() const;
    uint32_t tamanio() const;
    herramientas::utiles::Fecha fecha() const;
    std::string categoria() const;

    // SETTERS

    void bolsa_de_palabras(const std::vector<std::string> & bolsa_de_palabras_depurada);
    void tamanio(const uint32_t & tamanio_texto);
    void fecha(const herramientas::utiles::Fecha & fecha_contenido);
    void categoria(const std::string & categoria_contenido);

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
    uint32_t tamanio_texto;
    herramientas::utiles::Fecha fecha_contenido;
    std::string categoria_contenido;
};

};
};


