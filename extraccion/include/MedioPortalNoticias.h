#pragma once

// stl
#include <memory>

// medios digitales
#include <noticias/include/portal.h>
#include <noticias/include/lector.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping { namespace extraccion { namespace interfaceo {

    struct seccion {
        std::string nombre = "";
        uintmax_t cantidad_total = 0, tamanio_total = 0;
        herramientas::utiles::Fecha mas_reciente, mas_antiguo;
    };

class MedioPortalNoticias : public Medio {
public:
    explicit MedioPortalNoticias(std::shared_ptr<medios::noticias::portal> portal_noticias);
    explicit MedioPortalNoticias(herramientas::utiles::Json * json = nullptr);
    virtual ~MedioPortalNoticias();

    // GETTERS

    virtual std::string getGrupoMedio();
    virtual std::string etiqueta() const;

    virtual medios::noticias::portal * portal() const;
    virtual herramientas::utiles::Fecha fecha_ultima_noticia() const;
    virtual std::unordered_map<std::string, seccion> secciones() const;

    // SETTERS

    virtual void portal(std::shared_ptr<medios::noticias::portal> portal_noticias);
    virtual void fecha_ultima_noticia(const herramientas::utiles::Fecha & fecha);
    virtual void secciones(const std::unordered_map<std::string, seccion> & info_secciones);

    // METODOS

    virtual bool descargar_noticias(const medios::noticias::lector & lector_portal);

    virtual Medio * clonar();

    virtual std::string prefijoGrupo();

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IHashable

    virtual unsigned long long int hashcode();

    // CONSULTAS

private:

    //medios::noticias::portal * portal_noticias;
    std::shared_ptr<medios::noticias::portal> portal_noticias;

    herramientas::utiles::Fecha fecha_ultima_noticia_analizada;

    std::unordered_map<std::string, seccion> info_secciones;
};
};
};

};

