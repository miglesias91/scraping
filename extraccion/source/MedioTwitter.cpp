#include <extraccion/include/MedioTwitter.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/Logger.h>

// extraccion
#include <extraccion/include/ContenidoTwitter.h>

namespace scraping::extraccion::interfaceo {

MedioTwitter::MedioTwitter(const std::string & nombre_cuenta)
    : Medio(nullptr), cuenta_twitter(new medios::twitter::Cuenta(nombre_cuenta)), id_ultimo_tweet_analizado(0) {}
MedioTwitter::MedioTwitter(herramientas::utiles::Json * json)
    : Medio(json), cuenta_twitter(new medios::twitter::Cuenta()), id_ultimo_tweet_analizado(0) {}

MedioTwitter::~MedioTwitter() {
    delete this->cuenta_twitter;
}

std::string MedioTwitter::getGrupoMedio() {
    return scraping::ConfiguracionScraping::prefijoTwitter();
}

medios::twitter::Cuenta * MedioTwitter::cuenta() const {
    return this->cuenta_twitter;
}

void MedioTwitter::cuenta(medios::twitter::Cuenta * cuenta_twitter){
    this->cuenta_twitter = cuenta_twitter;
}

uintmax_t MedioTwitter::id_ultima_publicacion() const {
    return this->id_ultimo_tweet_analizado;
}

void MedioTwitter::id_ultima_publicacion(const uintmax_t & id_ultimo_tweet) {
    this->id_ultimo_tweet_analizado = id_ultimo_tweet;
}

bool MedioTwitter::descargar_tweets(const medios::twitter::Aplicacion & app) {

    std::vector<medios::twitter::Tweet*> tweets = app.leerUltimosTweets(this->cuenta_twitter, this->id_ultimo_tweet_analizado);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    std::for_each(tweets.begin(), tweets.end(),
        [=](medios::twitter::Tweet * tweet) {

        Contenido contenido_nuevo("", tweet->getTextoTweet(), "",tweet->getFechaCreacion());
        contenido_nuevo.asignarNuevoId();

        this->agregarContenidoParaAnalizar(&contenido_nuevo);

        gestor_analisis_diario.almacenarContenido(&contenido_nuevo);
        gestor_analisis_diario.almacenarIDActualContenido();

        delete tweet;
    });

    scraping::aplicacion::GestorMedios gestor_medios;
    if (0 < tweets.size())
    {// trajo por lo menos un tweet nuevo, entonces actualizo sus datos.
        this->id_ultimo_tweet_analizado = tweets[0]->getIdTweet();

        scraping::Logger::info("descargar_tweets: { cuenta = '" + this->cuenta_twitter->getNombre() + "' - id_ultimo_tweet_analizado = '" + std::to_string(this->id_ultimo_tweet_analizado) + "' }");

        // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
        gestor_analisis_diario.almacenarMedio(this);

        // almaceno el id del ultimo tweet analizado.
        gestor_medios.actualizarMedio(this);
    }

    return false;
}

Medio * MedioTwitter::clonar() {
    MedioTwitter * clon = new MedioTwitter();
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());
    clon->cuenta(new medios::twitter::Cuenta(this->cuenta_twitter->getNombre()));
    clon->id_ultima_publicacion(this->id_ultimo_tweet_analizado);

    clon->setMapaIDsContenidosAnalizados(this->getMapaIDsContenidosAnalizados());
    clon->setMapaIDsContenidosNoAnalizados(this->getMapaIDsContenidosNoAnalizados());
    clon->setMapaIDsContenidosHistoricos(this->getMapaIDsContenidosHistoricos());

    return clon;
}

std::string MedioTwitter::prefijoGrupo() {
    return scraping::ConfiguracionScraping::prefijoMedio();
}

bool MedioTwitter::armarJson() {
    this->getJson()->reset();

    this->getJson()->agregarAtributoValor("nombre_cuenta", this->cuenta_twitter->getNombre());
    this->getJson()->agregarAtributoValor("id_ultimo_tweet_analizado", this->id_ultimo_tweet_analizado);

    return true;
}

bool MedioTwitter::parsearJson() {
    std::string nombre_cuenta = this->getJson()->getAtributoValorString("nombre_cuenta");
    this->id_ultimo_tweet_analizado = this->getJson()->getAtributoValorUint("id_ultimo_tweet_analizado");

    this->cuenta_twitter->setNombre(nombre_cuenta);

    return true;
}

uintmax_t MedioTwitter::hashcode() {
    return herramientas::utiles::IHashable::hashear(this->cuenta_twitter->getNombre());
}

}