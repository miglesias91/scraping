#include <extraccion/include/MedioPortalNoticias.h>

// stl
#include <algorithm>

// medios digitales
#include <noticias/include/fabrica_portales.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/Logger.h>

namespace scraping::extraccion::interfaceo {

MedioPortalNoticias::MedioPortalNoticias(std::shared_ptr<medios::noticias::portal> portal_noticias)
    : Medio(scraping::ConfiguracionScraping::prefijoPortalNoticias(), nullptr), portal_noticias(portal_noticias), fecha_ultima_noticia_analizada(0, 0, 0) {}

MedioPortalNoticias::MedioPortalNoticias(herramientas::utiles::Json * json)
    : Medio(scraping::ConfiguracionScraping::prefijoPortalNoticias(), json), portal_noticias(nullptr) {}

MedioPortalNoticias::~MedioPortalNoticias() {
    //delete this->portal_noticias;
}

std::string MedioPortalNoticias::getGrupoMedio() {
    return scraping::ConfiguracionScraping::prefijoPortalNoticias();
}

medios::noticias::portal * MedioPortalNoticias::portal() const {
    return this->portal_noticias.get();
}

void MedioPortalNoticias::portal(std::shared_ptr<medios::noticias::portal> portal_noticias) {
    this->portal_noticias = portal_noticias;
}

herramientas::utiles::Fecha MedioPortalNoticias::fecha_ultima_noticia() const {
    return this->fecha_ultima_noticia_analizada;
}

void MedioPortalNoticias::fecha_ultima_noticia(const herramientas::utiles::Fecha & fecha) {
    this->fecha_ultima_noticia_analizada = fecha;
}

bool MedioPortalNoticias::descargar_noticias(const medios::noticias::lector & lector) {
    lector.leer(this->portal_noticias.get(), this->fecha_ultima_noticia_analizada);

    std::vector<medios::noticias::noticia*> todas_las_noticias;
    this->portal_noticias->noticias(&todas_las_noticias);

    if (0 == todas_las_noticias.size()) {
        return false;
    }

    std::sort(todas_las_noticias.begin(), todas_las_noticias.end(), [](medios::noticias::noticia * a, medios::noticias::noticia * b) {
        return a->fecha() < b->fecha();
    });

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    std::for_each(todas_las_noticias.begin(), todas_las_noticias.end(),
        [=](medios::noticias::noticia * noticia) {

        Contenido contenido_nuevo(noticia->titulo(), noticia->contenido(), noticia->seccion(), noticia->fecha());
        contenido_nuevo.asignarNuevoId();

        this->agregarContenidoParaAnalizar(&contenido_nuevo);

        gestor_analisis_diario.almacenarContenido(&contenido_nuevo);
        gestor_analisis_diario.almacenarIDActualContenido();

        this->fecha_ultima_noticia_analizada = noticia->fecha();

        // delete noticia;
    });

    scraping::Logger::info("descargar_noticias: { portal = '" + this->portal_noticias->web() + "' - fecha_ultima_publicacion_analizada = '" + this->fecha_ultima_noticia_analizada.getStringAAAAMMDDHHmmSS() + "' }");

    // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
    gestor_analisis_diario.almacenarMedio(this);

    // almaceno el id del ultimo publicacion analizado.
    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.actualizarMedio(this);

    return true;
}

Medio * MedioPortalNoticias::clonar() {
    MedioPortalNoticias * clon = new MedioPortalNoticias();
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());
    //clon->portal(this->portal_noticias->clon());
    clon->portal(this->portal_noticias);

    clon->setMapaIDsContenidosAnalizados(this->getMapaIDsContenidosAnalizados());
    clon->setMapaIDsContenidosNoAnalizados(this->getMapaIDsContenidosNoAnalizados());
    clon->setMapaIDsContenidosHistoricos(this->getMapaIDsContenidosHistoricos());

    return clon;
}

std::string MedioPortalNoticias::prefijoGrupo() {
    return scraping::ConfiguracionScraping::prefijoMedio();
}

bool MedioPortalNoticias::armarJson() {
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("web_portal", this->portal_noticias->web());
    this->getJson()->agregarAtributoValor("fecha_ultima_publicacion_analizada", this->fecha_ultima_noticia_analizada.getStringAAAAMMDDHHmmSS());

    return true;
}

bool MedioPortalNoticias::parsearJson() {
    std::string web_portal = this->getJson()->getAtributoValorString("web_portal");
    std::string fecha_ultima_publicacion_analizada = this->getJson()->getAtributoValorString("fecha_ultima_publicacion_analizada");

    this->portal_noticias = medios::noticias::fabrica_portales::nuevo(web_portal);
    this->fecha_ultima_noticia_analizada = herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(fecha_ultima_publicacion_analizada);

    return true;
}

uintmax_t MedioPortalNoticias::hashcode() {
    return herramientas::utiles::IHashable::hashear(this->portal_noticias->web());
}
}