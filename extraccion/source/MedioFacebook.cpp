#include <extraccion/include/MedioFacebook.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/Logger.h>

namespace scraping::extraccion::interfaceo {

MedioFacebook::MedioFacebook(const std::string & nombre_pagina) : Medio(nullptr), pagina_facebook(new medios::facebook::Pagina(nombre_pagina)) {}
MedioFacebook::MedioFacebook(herramientas::utiles::Json * json) : Medio(json), pagina_facebook(new medios::facebook::Pagina()) {}

MedioFacebook::~MedioFacebook() {
    delete this->pagina_facebook;
}

std::string MedioFacebook::getGrupoMedio() {
    return scraping::ConfiguracionScraping::prefijoFacebook();
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

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    std::for_each(publicaciones.begin(), publicaciones.end(),
        [=](medios::facebook::Publicacion * publicacion) {

        Contenido contenido_nuevo("", publicacion->getTextoPublicacion(), "", publicacion->getFechaCreacion());
        contenido_nuevo.asignarNuevoId();

        this->agregarContenidoParaAnalizar(&contenido_nuevo);

        gestor_analisis_diario.almacenarContenido(&contenido_nuevo);
        gestor_analisis_diario.almacenarIDActualContenido();

        delete publicacion;
    });

    scraping::aplicacion::GestorMedios gestor_medios;
    if (0 < publicaciones.size())
    {// trajo por lo menos un publicacion nuevo, entonces actualizo sus datos.
        this->fecha_ultima_publicacion_analizada = publicaciones[0]->getFechaCreacion();

        scraping::Logger::info("descargar_publicacion: { pagina = '" + this->pagina_facebook->getNombre() + "' - fecha_ultima_publicacion_analizada = '" + this->fecha_ultima_publicacion_analizada.getStringAAAAMMDDHHmmSS() + "' }");

        // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
        gestor_analisis_diario.almacenarMedio(this);

        // almaceno el id del ultimo publicacion analizado.
        gestor_medios.actualizarMedio(this);
    }

    return false;
}

Medio * MedioFacebook::clonar() {
    MedioFacebook * clon = new MedioFacebook();
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());
    clon->pagina(new medios::facebook::Pagina(this->pagina_facebook->getNombre()));
    clon->fecha_ultima_publicacion(this->fecha_ultima_publicacion_analizada);

    clon->setMapaIDsContenidosAnalizados(this->getMapaIDsContenidosAnalizados());
    clon->setMapaIDsContenidosNoAnalizados(this->getMapaIDsContenidosNoAnalizados());
    clon->setMapaIDsContenidosHistoricos(this->getMapaIDsContenidosHistoricos());

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

}