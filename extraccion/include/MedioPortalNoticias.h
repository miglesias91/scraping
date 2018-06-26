#pragma once

// medios digitales
#include <noticias/include/portal.h>
#include <noticias/include/lector.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping::extraccion::interfaceo {
class MedioPortalNoticias : public Medio {
public:
    explicit MedioPortalNoticias(medios::noticias::portal * portal_noticias);
    explicit MedioPortalNoticias(herramientas::utiles::Json * json = nullptr);
    virtual ~MedioPortalNoticias();

    // GETTERS

    virtual std::string getGrupoMedio();

    virtual medios::noticias::portal * portal() const;
    virtual herramientas::utiles::Fecha fecha_ultima_noticia() const;

    // SETTERS

    virtual void portal(medios::noticias::portal * portal_noticias);
    virtual void fecha_ultima_noticia(const herramientas::utiles::Fecha & fecha);

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

    std::shared_ptr<medios::noticias::portal*> portal_noticias;

    herramientas::utiles::Fecha fecha_ultima_noticia_analizada;
};

};

