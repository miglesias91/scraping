#include <extraccion/include/MedioPortalNoticias.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/Logger.h>

namespace scraping::extraccion::interfaceo {

MedioPortalNoticias::MedioPortalNoticias(medios::noticias::portal * portal_noticias)
    : Medio(nullptr), portal_noticias(portal_noticias), fecha_ultima_noticia_analizada(0, 0, 0) {}
MedioPortalNoticias::MedioPortalNoticias(herramientas::utiles::Json * json) : Medio(json), portal_noticias(nullptr) {}

MedioPortalNoticias::~MedioPortalNoticias() {
    delete this->portal_noticias;
}

std::string MedioPortalNoticias::getGrupoMedio() {
    return scraping::ConfiguracionScraping::prefijoPortalNoticias();
}

medios::noticias::portal * MedioPortalNoticias::portal() const{
    return this->portal_noticias;
}

void MedioPortalNoticias::portal(medios::noticias::portal * portal_noticias) {
    this->portal_noticias = portal_noticias;
}

herramientas::utiles::Fecha MedioPortalNoticias::fecha_ultima_noticia() const {
    return this->fecha_ultima_noticia_analizada;
}

void MedioPortalNoticias::fecha_ultima_noticia(const herramientas::utiles::Fecha & fecha) {
    this->fecha_ultima_noticia_analizada = fecha;
}

bool MedioPortalNoticias::descargar_noticias(const medios::noticias::lector & lector) {
    lector.leer(this->portal_noticias, this->fecha_ultima_noticia_analizada);

    std::vector<medios::noticias::noticia*> todas_las_noticias;
    this->portal_noticias->noticias(&todas_las_noticias);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    std::for_each(todas_las_noticias.begin(), todas_las_noticias.end(),
        [=](medios::noticias::noticia * noticia) {

        Contenido contenido_nuevo(noticia->titulo(), noticia->contenido(), noticia->seccion(), noticia->fecha());
        contenido_nuevo.asignarNuevoId();

        this->agregarContenidoParaAnalizar(&contenido_nuevo);

        gestor_analisis_diario.almacenarContenido(&contenido_nuevo);
        gestor_analisis_diario.almacenarIDActualContenido();

        delete noticia;
    });

    scraping::aplicacion::GestorMedios gestor_medios;
    if (0 < todas_las_noticias.size())
    {// trajo por lo menos un publicacion nuevo, entonces actualizo sus datos.
        this->fecha_ultima_noticia_analizada = todas_las_noticias[0]->fecha();

        scraping::Logger::info("descargar_noticias: { portal = '" + this->portal_noticias->getNombre() + "' - fecha_ultima_publicacion_analizada = '" + this->portal_noticias->getFechaUltimaPublicacionAnalizada().getStringAAAAMMDDHHmmSS() + "' }");

        // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
        gestor_analisis_diario.almacenarMedio(this);

        // almaceno el id del ultimo publicacion analizado.
        gestor_medios.actualizarMedio(this);
    }

    return false;
}

bool MedioPortalNoticias::descargar_noticias(const medios::noticias::lector & lector_portal) {
    return false;
}

Medio * MedioPortalNoticias::clonar() {
    MedioPortalNoticias * clon = new MedioPortalNoticias();
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());
    clon->portal(this->portal);

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

    this->getJson()->agregarAtributoValor("nombre_portal", this->portal_noticias->getNombre());
    this->getJson()->agregarAtributoValor("fecha_ultima_publicacion_analizada", this->portal_noticias->getFechaUltimaPublicacionAnalizada().getStringAAAAMMDDHHmmSS());

    return true;
}

bool MedioPortalNoticias::parsearJson() {
    std::string nombre_portal = this->getJson()->getAtributoValorString("nombre_portal");
    std::string fecha_ultima_publicacion_analizada = this->getJson()->getAtributoValorString("fecha_ultima_publicacion_analizada");

    this->portal_noticias->setNombre(nombre_portal);
    this->portal_noticias->setFechaUltimaPublicacionAnalizada(herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(fecha_ultima_publicacion_analizada));

    return true;
}

uintmax_t MedioPortalNoticias::hashcode() {
    return herramientas::utiles::IHashable::hashear(this->portal_noticias->getNombre());
}
}