#include <analisis/include/Analizador.h>

// scraping
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/ConfiguracionScraping.h>

// analisis
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
    });
    return true;
}

bool Analizador::analizar_facebook() const {
    return false;
}

bool Analizador::analizar_portales() const {
    return false;
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

    });



    return false;
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

