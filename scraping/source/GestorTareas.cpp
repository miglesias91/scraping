#include <scraping/include/GestorTareas.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/Logger.h>

// depuracion
#include <depuracion/include/Depurador.h>
#include <depuracion/include/ContenidoDepurable.h>

// analisis
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/ResultadoFuerzaEnNoticia.h>
#include <analisis/include/Analizador.h>
#include <analisis/include/ContenidoAnalizable.h>

// preparacion
#include <preparacion/include/Preparador.h>
#include <preparacion/include/ResultadoAnalisisContenido.h>
#include <preparacion/include/ResultadoAnalisisMedio.h>
#include <preparacion/include/ResultadoAnalisisDiario.h>

// extraccion
#include <extraccion/include/extractor.h>
#include <extraccion/include/MedioFacebook.h>
#include <extraccion/include/MedioTwitter.h>
#include <extraccion/include/MedioPortalNoticias.h>

using namespace scraping::aplicacion;

GestorTareas::GestorTareas() {}

GestorTareas::~GestorTareas() {}

// extraccion
bool GestorTareas::extraer_facebook() {
    extraccion::extractor extractor;
    return extractor.extraer_facebook();
}

bool GestorTareas::extraer_twitter() {
    extraccion::extractor extractor;
    return extractor.extraer_twitter();
}

bool GestorTareas::extraer_portales() {
    extraccion::extractor extractor;
    return extractor.extraer_portales();
}

// depuracion
bool GestorTareas::depurar_twitter() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioTwitter*> cuentas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioTwitter>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas);

    depuracion::Depurador depu;
    std::for_each(cuentas.begin(), cuentas.end(), [=, &depu](scraping::extraccion::interfaceo::MedioTwitter * cuenta) {
        depu.depurar(cuenta);
        delete cuenta;
    });
    return true;
}

bool GestorTareas::depurar_facebook() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioFacebook*> paginas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioFacebook>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas);

    depuracion::Depurador depu;
    std::for_each(paginas.begin(), paginas.end(), [=, &depu](scraping::extraccion::interfaceo::MedioFacebook * pagina) {
        depu.depurar(pagina);
        delete pagina;
    });
    return true;
}

bool GestorTareas::depurar_portales() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioPortalNoticias*> portales;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioPortalNoticias>(scraping::ConfiguracionScraping::prefijoPortalNoticias(), portales);

    depuracion::Depurador depu;
    std::for_each(portales.begin(), portales.end(), [=, &depu](scraping::extraccion::interfaceo::MedioPortalNoticias * portal) {
        depu.depurar(portal);
        delete portal;
    });
    return true;
}

// analisis
bool GestorTareas::analizar_twitter() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioTwitter*> cuentas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioTwitter>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas);

    analisis::Analizador analizador;
    std::for_each(cuentas.begin(), cuentas.end(), [=](scraping::extraccion::interfaceo::MedioTwitter * cuenta) {
        analizador.analizar(cuenta);
        delete cuenta;
    });
    return true;
}

bool GestorTareas::analizar_facebook() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioFacebook*> paginas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioFacebook>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas);

    analisis::Analizador analizador;
    std::for_each(paginas.begin(), paginas.end(), [=](scraping::extraccion::interfaceo::MedioFacebook * pagina) {
        analizador.analizar(pagina);
        delete pagina;
    });
    return true;
}

bool GestorTareas::analizar_portales() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioPortalNoticias*> portales;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioPortalNoticias>(scraping::ConfiguracionScraping::prefijoPortalNoticias(), portales);

    analisis::Analizador analizador;
    std::for_each(portales.begin(), portales.end(), [=](scraping::extraccion::interfaceo::MedioPortalNoticias * portal) {
        analizador.analizar(portal);
        delete portal;
    });
    return true;
}

// preparacion
bool GestorTareas::preparar_twitter() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioTwitter*> cuentas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioTwitter>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas);

    preparacion::Preparador preparador;
    std::for_each(cuentas.begin(), cuentas.end(), [=](scraping::extraccion::interfaceo::MedioTwitter * cuenta) {
        preparador.preparar(cuenta);
        delete cuenta;
    });
    return true;
}

bool GestorTareas::preparar_facebook() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioFacebook*> paginas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioFacebook>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas);

    preparacion::Preparador preparador;
    std::for_each(paginas.begin(), paginas.end(), [=](scraping::extraccion::interfaceo::MedioFacebook * pagina) {
        preparador.preparar(pagina);
        delete pagina;
    });
    return true;
}

bool GestorTareas::preparar_portales() {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioPortalNoticias*> portales;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioPortalNoticias>(scraping::ConfiguracionScraping::prefijoPortalNoticias(), portales);

    preparacion::Preparador preparador;
    std::for_each(portales.begin(), portales.end(), [=](scraping::extraccion::interfaceo::MedioPortalNoticias * portal) {
        preparador.preparar(portal);
        delete portal;
    });
    return true;
}

void GestorTareas::scrapear_facebook() {
    extraer_facebook();
    depurar_facebook();
    analizar_facebook();
    preparar_facebook();
}

void GestorTareas::scrapear_twitter() {
    extraer_twitter();
    depurar_twitter();
    analizar_twitter();
    preparar_twitter();
}

void GestorTareas::scrapear_portales() {
    extraer_portales();
    depurar_portales();
    analizar_portales();
    preparar_portales();
}