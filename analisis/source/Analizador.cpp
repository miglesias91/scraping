#include <analisis/include/Analizador.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/ConfiguracionScraping.h>

// analisis
#include <analisis/include/ContenidoAnalizable.h>
#include <analisis/include/CantidadDeApariciones.h>
#include <analisis/include/FuerzaEnNoticia.h>
#include <analisis/include/Sentimiento.h>

// preparacion
#include <preparacion/include/Preparador.h>
#include <preparacion/include/ResultadoAnalisisContenido.h>
#include <preparacion/include/ResultadoAnalisisMedio.h>
#include <preparacion/include/ResultadoAnalisisDiario.h>

// extraccion
#include <extraccion/include/MedioTwitter.h>
#include <extraccion/include/MedioFacebook.h>
#include <extraccion/include/MedioPortalNoticias.h>

using namespace scraping::analisis;

Analizador::Analizador()
{
}

Analizador::~Analizador()
{
}

bool Analizador::analizar_twitter() const {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioTwitter*> cuentas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioTwitter>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas);

    std::for_each(cuentas.begin(), cuentas.end(), [=](scraping::extraccion::interfaceo::MedioTwitter * cuenta) {
        this->analizar(cuenta);
        delete cuenta;
    });
    return true;
}

bool Analizador::analizar_facebook() const {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioFacebook*> paginas;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioFacebook>(scraping::ConfiguracionScraping::prefijoFacebook(), paginas);

    std::for_each(paginas.begin(), paginas.end(), [=](scraping::extraccion::interfaceo::MedioFacebook * pagina) {
        this->analizar(pagina);
        delete pagina;
    });
    return true;
}

bool Analizador::analizar_portales() const {
    scraping::aplicacion::GestorMedios gestor_medios;

    std::vector<scraping::extraccion::interfaceo::MedioPortalNoticias*> portales;
    gestor_medios.recuperar<scraping::extraccion::interfaceo::MedioPortalNoticias>(scraping::ConfiguracionScraping::prefijoPortalNoticias(), portales);

    std::for_each(portales.begin(), portales.end(), [=](scraping::extraccion::interfaceo::MedioPortalNoticias * portal) {
        this->analizar(portal);
        delete portal;
    });
    return true;
}

bool Analizador::analizar(scraping::extraccion::Medio * medio) const {
    std::vector<uintmax_t> ids_para_analizar;
    medio->ids_para_analizar(&ids_para_analizar);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;
    std::vector<depuracion::ContenidoDepurado*> contenidos_a_analizar;
    std::for_each(ids_para_analizar.begin(), ids_para_analizar.end(), [=, &contenidos_a_analizar](uintmax_t id) {
        depuracion::ContenidoDepurado * contenido = new depuracion::ContenidoDepurado();
        contenido->setId(new herramientas::utiles::ID(id));

        gestor_analisis.recuperar(contenido);

        contenidos_a_analizar.push_back(contenido);
    });

    std::vector<preparacion::ResultadoAnalisisContenido*> resultados;
    std::for_each(contenidos_a_analizar.begin(), contenidos_a_analizar.end(), [=, &resultados](depuracion::ContenidoDepurado * contenido) {
        analisis::IAnalizable * contenido_analizable = new analisis::ContenidoAnalizable(contenido->getBolsaDePalabras(), contenido->tamanio());

        preparacion::ResultadoAnalisisContenido * resultado_analisis_contenido = new preparacion::ResultadoAnalisisContenido();
        resultado_analisis_contenido->setId(contenido->getId()->copia());
        resultado_analisis_contenido->fecha(contenido->fecha());
        resultado_analisis_contenido->categoria(contenido->categoria());

        this->analizar(contenido_analizable, resultado_analisis_contenido);

        resultados.push_back(resultado_analisis_contenido);

        delete contenido_analizable;
        delete contenido;
    });

    scraping::aplicacion::GestorMedios gestor_medios;
    std::for_each(resultados.begin(), resultados.end(), [=](preparacion::ResultadoAnalisisContenido * resultado) {
        gestor_analisis.almacenarResultadoAnalisis(resultado);

        medio->contenido_analizado(resultado->fecha().getStringAAAAMMDD(), resultado->getId()->numero());
        gestor_medios.actualizarMedio(medio);

        delete resultado;
    });

    return true;
}

void Analizador::analizar(IAnalizable * contenido_a_analizar, ResultadoAnalisis * resultado_analisis) const {
    // aplico 'fuerza en noticia'
    tecnicas::FuerzaEnNoticia fuerza_en_noticia;
    tecnicas::ResultadoFuerzaEnNoticia * resultado_fuerza_en_noticia = new tecnicas::ResultadoFuerzaEnNoticia();
    fuerza_en_noticia.aplicar(contenido_a_analizar, resultado_fuerza_en_noticia);
    resultado_analisis->setResultadoFuerzaEnNoticia(resultado_fuerza_en_noticia);

    // aplico 'sentimiento'
    tecnicas::Sentimiento sentimiento;
    tecnicas::ResultadoSentimiento * resultado_sentimiento = new tecnicas::ResultadoSentimiento();
    sentimiento.aplicar(contenido_a_analizar, resultado_sentimiento);
    resultado_analisis->setResultadoSentimiento(resultado_sentimiento);
}

// GETTERS

// SETTERS

// METODOS

// CONSULTAS

