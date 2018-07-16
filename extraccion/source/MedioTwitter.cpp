#include <extraccion/include/MedioTwitter.h>

// stl
#include <algorithm>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorAnalisisDiario.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/Logger.h>

namespace scraping::extraccion::interfaceo {

MedioTwitter::MedioTwitter(const std::string & nombre_cuenta)
    : Medio(scraping::ConfiguracionScraping::prefijoTwitter(), nullptr), cuenta_twitter(new medios::twitter::Cuenta(nombre_cuenta)), id_ultimo_tweet_analizado(0) {}

MedioTwitter::MedioTwitter(herramientas::utiles::Json * json)
    : Medio(scraping::ConfiguracionScraping::prefijoTwitter(), json), cuenta_twitter(new medios::twitter::Cuenta()), id_ultimo_tweet_analizado(0) {}

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
    
    scraping::Logger::info("twitter", "extraccion: descargados " + std::to_string(tweets.size()) + " tweets de '" + this->cuenta_twitter->getNombre() + "'.");

    if (0 == tweets.size()) {  // si no descargo nada, entonces devuelvo false.
        return false;
    }

    // lo doy vuelta recorrerlos de mas antiguo a mas reciente: ahora me qeda 
    std::reverse(tweets.begin(), tweets.end());

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis_diario;
    std::for_each(tweets.begin(), tweets.end(),
        [=](medios::twitter::Tweet * tweet) {

        Contenido contenido_nuevo("", tweet->getTextoTweet(), "",tweet->getFechaCreacion());

        mutex_modificacion_id_contenido.lock();
        contenido_nuevo.asignarNuevoId();
        gestor_analisis_diario.almacenarIDActualContenido();
        mutex_modificacion_id_contenido.unlock();

        this->nuevo(&contenido_nuevo);
        gestor_analisis_diario.almacenarContenido(&contenido_nuevo);

        this->id_ultimo_tweet_analizado = tweet->getIdTweet();

        delete tweet;
    });

    // almaceno los datos de ids analizados y no analizados, agruapados por fecha.
    gestor_analisis_diario.almacenarMedio(this);

    scraping::aplicacion::GestorMedios gestor_medios;
    // almaceno el id del ultimo tweet analizado.
    gestor_medios.actualizarMedio(this);

    return true;
}

Medio * MedioTwitter::clonar() {
    MedioTwitter * clon = new MedioTwitter(this->cuenta_twitter->getNombre());
    clon->setId(this->getId()->copia());
    clon->setJson(this->getJson()->clonar());
    clon->id_ultima_publicacion(this->id_ultimo_tweet_analizado);

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