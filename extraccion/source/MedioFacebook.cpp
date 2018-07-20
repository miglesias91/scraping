#include <extraccion/include/MedioFacebook.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/Logger.h>

namespace scraping { namespace extraccion { namespace interfaceo {

MedioFacebook::MedioFacebook(const std::string & nombre_pagina)
    : Medio(scraping::ConfiguracionScraping::prefijoFacebook(), nullptr), pagina_facebook(new medios::facebook::Pagina(nombre_pagina)) {}

MedioFacebook::MedioFacebook(herramientas::utiles::Json * json)
    : Medio(scraping::ConfiguracionScraping::prefijoFacebook(), json), pagina_facebook(new medios::facebook::Pagina()) {}

MedioFacebook::~MedioFacebook() {
    delete this->pagina_facebook;
}

std::string MedioFacebook::getGrupoMedio() {
    return scraping::ConfiguracionScraping::prefijoFacebook();
}

std::string MedioFacebook::etiqueta() const {
    return this->pagina_facebook->getNombre();
}

medios::facebook::Pagina * MedioFacebook::pagina() const {
    return this->pagina_facebook;
}

void MedioFacebook::pagina(medios::facebook::Pagina * pagina_facebook) {
    this->pagina_facebook = pagina_facebook;
}

herramientas::utiles::Fecha MedioFacebook::fecha_ultima_publicacion() const {
    return this->fecha_ultima_publicacion_analizada;
}

void MedioFacebook::fecha_ultima_publicacion(const herramientas::utiles::Fecha & fecha) {
    this->fecha_ultima_publicacion_analizada = fecha;
}

bool MedioFacebook::descargar_publicaciones(const medios::facebook::aplicacion & app) {

    std::vector<medios::facebook::Publicacion*> publicaciones = app.leer(this->pagina_facebook, this->fecha_ultima_publicacion_analizada);

    scraping::Logger::info("facebook", "extraccion: descargadas " + std::to_string(publicaciones.size()) + " publicaciones de '" + this->pagina_facebook->getNombre() + "'.");
    if (0 == publicaciones.size()) {  // si no descargo nada, entonces devuelvo false.
        return false;
    }

    std::reverse(publicaciones.begin(), publicaciones.end());

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    std::for_each(publicaciones.begin(), publicaciones.end(),
        [=](medios::facebook::Publicacion * publicacion) {

        Contenido contenido_nuevo("", publicacion->getTextoPublicacion(), "", publicacion->getFechaCreacion());
        
        mutex_modificacion_id_contenido.lock();
        contenido_nuevo.asignarNuevoId();
        gestor_analisis_diario.almacenarIDActualContenido();
        mutex_modificacion_id_contenido.unlock();

        this->nuevo(&contenido_nuevo);
        gestor_analisis_diario.almacenarContenido(&contenido_nuevo);

        this->fecha_ultima_publicacion_analizada = publicacion->getFechaCreacion();

        if(publicacion->getTextoPublicacion().size()) {
            this->tamanio_total += std::log10(publicacion->getTextoPublicacion().size());
        }

        delete publicacion;
    });
    // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
    //gestor_analisis_diario.almacenarMedio(this);

    scraping::aplicacion::GestorMedios gestor_medios;
    // almaceno el id del ultimo publicacion analizado.
    gestor_medios.actualizarMedio(this);

    return true;
}

Medio * MedioFacebook::clonar() {
    MedioFacebook * clon = new MedioFacebook(this->pagina_facebook->getNombre());
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());
    clon->fecha_ultima_publicacion(this->fecha_ultima_publicacion_analizada);
    
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

std::string MedioFacebook::prefijoGrupo() {
    return scraping::ConfiguracionScraping::prefijoMedio();
}

bool MedioFacebook::armarJson() {
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("nombre_pagina", this->pagina_facebook->getNombre());
    this->getJson()->agregarAtributoValor("fecha_ultima_publicacion_analizada", this->fecha_ultima_publicacion_analizada.getStringAAAAMMDDHHmmSS());

    return true;
}

bool MedioFacebook::parsearJson() {
    std::string nombre_pagina = this->getJson()->getAtributoValorString("nombre_pagina");
    std::string fecha_ultima_publicacion_analizada = this->getJson()->getAtributoValorString("fecha_ultima_publicacion_analizada");

    this->pagina_facebook->setNombre(nombre_pagina);
    this->fecha_ultima_publicacion_analizada = herramientas::utiles::Fecha::parsearFormatoAAAAMMDDHHmmSS(fecha_ultima_publicacion_analizada);

    return true;
}

uintmax_t MedioFacebook::hashcode() {
    return herramientas::utiles::IHashable::hashear(this->pagina_facebook->getNombre());
}

}}}