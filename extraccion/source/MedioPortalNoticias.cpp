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

std::string MedioPortalNoticias::etiqueta() const {
    return this->portal_noticias->web();
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

std::unordered_map<std::string, seccion> MedioPortalNoticias::secciones() const {
    return this->info_secciones;
}

void MedioPortalNoticias::fecha_ultima_noticia(const herramientas::utiles::Fecha & fecha) {
    this->fecha_ultima_noticia_analizada = fecha;
}

void MedioPortalNoticias::secciones(const std::unordered_map<std::string, seccion>& info_secciones) {
    this->info_secciones = info_secciones;
}

bool MedioPortalNoticias::descargar_noticias(const medios::noticias::lector & lector) {
    lector.leer(this->portal_noticias.get(), this->fecha_ultima_noticia_analizada);

    std::vector<medios::noticias::noticia*> todas_las_noticias;
    this->portal_noticias->noticias(&todas_las_noticias);

    scraping::Logger::info("portales", "extraccion: descargadas " + std::to_string(todas_las_noticias.size()) + " noticias de '" + this->portal_noticias->web() + "'.");

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

        mutex_modificacion_id_contenido.lock();
        contenido_nuevo.asignarNuevoId();
        gestor_analisis_diario.almacenarIDActualContenido();
        mutex_modificacion_id_contenido.unlock();

        this->nuevo(&contenido_nuevo);
        //gestor_analisis_diario.almacenarContenido(&contenido_nuevo);
        gestor_analisis_diario.modificarContenido(&contenido_nuevo);  // si existe un contenido con el mismo id, lo reemplaza

        this->fecha_ultima_noticia_analizada = noticia->fecha();
    });

    std::unordered_map<std::string, std::vector<medios::noticias::noticia*>> noticias_por_seccion;
    this->portal_noticias->noticias(&noticias_por_seccion);

    // guardo info de cada seccion
    std::for_each(noticias_por_seccion.begin(), noticias_por_seccion.end(), [=](std::pair<std::string, std::vector<medios::noticias::noticia*>> seccion_noticias) {
        seccion info = this->info_secciones[seccion_noticias.first];
        info.cantidad_total += seccion_noticias.second.size();
        std::sort(seccion_noticias.second.begin(), seccion_noticias.second.end(), [](medios::noticias::noticia * a, medios::noticias::noticia * b) {
            return a->fecha() < b->fecha();
        });
        if (info.mas_antiguo == herramientas::utiles::Fecha() || info.mas_antiguo > (*seccion_noticias.second.begin())->fecha()) {
            info.mas_antiguo = (*seccion_noticias.second.begin())->fecha();
        }
        info.mas_reciente = (*(seccion_noticias.second.end() - 1))->fecha();

        std::for_each(seccion_noticias.second.begin(), seccion_noticias.second.end(), [&info](medios::noticias::noticia * noti){
            if(noti->contenido().size()) {
                info.tamanio_total += noti->contenido().size();
            }
        });

        this->info_secciones[seccion_noticias.first] = info;
    });

    // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
    //gestor_analisis_diario.almacenarMedio(this);

    // almaceno el id del ultimo publicacion analizado.
    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.actualizarMedio(this);

    return true;
}

Medio * MedioPortalNoticias::clonar() {
    MedioPortalNoticias * clon = new MedioPortalNoticias();
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());
    clon->portal(this->portal_noticias);
    clon->secciones(this->info_secciones);

    std::unordered_map<std::string, std::vector<uintmax_t>> mapa;

    this->ids_para_depurar(&mapa);
    clon->set_ids_para_depurar(mapa);

    this->ids_para_analizar(&mapa);
    clon->set_ids_para_analizar(mapa);

    this->ids_para_preparar(&mapa);
    clon->set_ids_para_preparar(mapa);

    this->ids_historicos(&mapa);
    clon->set_ids_historicos(mapa);

    return clon;
}

std::string MedioPortalNoticias::prefijoGrupo() {
    return scraping::ConfiguracionScraping::prefijoMedio();
}

bool MedioPortalNoticias::armarJson() {
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("web_portal", this->portal_noticias->web());
    this->getJson()->agregarAtributoValor("fecha_ultima_publicacion_analizada", this->fecha_ultima_noticia_analizada.getStringAAAAMMDDHHmmSS());

    std::vector<herramientas::utiles::Json*> json_info_secciones;
    std::for_each(this->info_secciones.begin(), this->info_secciones.end(), [=, &json_info_secciones](std::pair<std::string, seccion> info_seccion) {
        herramientas::utiles::Json * json_info_seccion = new herramientas::utiles::Json();
        json_info_seccion->agregarAtributoValor("nombre", info_seccion.first);
        json_info_seccion->agregarAtributoValor("cantidad_total", info_seccion.second.cantidad_total);
        json_info_seccion->agregarAtributoValor("tamanio_total", info_seccion.second.tamanio_total);
        json_info_seccion->agregarAtributoValor("mas_antiguo", info_seccion.second.mas_antiguo.getStringAAAAMMDDHHmmSS());
        json_info_seccion->agregarAtributoValor("mas_reciente", info_seccion.second.mas_reciente.getStringAAAAMMDDHHmmSS());

        json_info_secciones.push_back(json_info_seccion);
    });
    this->getJson()->agregarAtributoArray("secciones", json_info_secciones);

    std::for_each(json_info_secciones.begin(), json_info_secciones.end(), [](herramientas::utiles::Json* json) { delete json; });
    return true;
}

bool MedioPortalNoticias::parsearJson() {
    std::string web_portal = this->getJson()->getAtributoValorString("web_portal");
    std::string fecha_ultima_publicacion_analizada = this->getJson()->getAtributoValorString("fecha_ultima_publicacion_analizada");
    std::vector<herramientas::utiles::Json*> json_info_secciones = this->getJson()->getAtributoArrayJson("secciones");

    this->portal_noticias = medios::noticias::fabrica_portales::nuevo(web_portal);
    this->fecha_ultima_noticia_analizada = herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(fecha_ultima_publicacion_analizada);

    std::for_each(json_info_secciones.begin(), json_info_secciones.end(), [=](herramientas::utiles::Json* json_info_seccion) {
        seccion info_seccion;
        info_seccion.nombre = json_info_seccion->getAtributoValorString("nombre");
        info_seccion.cantidad_total = json_info_seccion->getAtributoValorUint("cantidad_total");
        info_seccion.tamanio_total = json_info_seccion->getAtributoValorUint("tamanio_total");
        info_seccion.mas_antiguo = herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(json_info_seccion->getAtributoValorString("mas_antiguo"));
        info_seccion.mas_reciente = herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(json_info_seccion->getAtributoValorString("mas_reciente"));

        this->info_secciones[info_seccion.nombre] = info_seccion;

        delete json_info_seccion;
    });

    return true;
}

uintmax_t MedioPortalNoticias::hashcode() {
    return herramientas::utiles::IHashable::hashear(this->portal_noticias->web());
}
}