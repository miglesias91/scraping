#pragma once

// medios digitales
#include <twitter/include/Aplicacion.h>
#include <twitter/include/Cuenta.h>

// extraccion
#include <extraccion/include/Medio.h>

namespace scraping { namespace extraccion { namespace interfaceo {
class MedioTwitter : public Medio {
public:
    explicit MedioTwitter(const std::string & nombre_cuenta);
    explicit MedioTwitter(herramientas::utiles::Json * json = nullptr);
    virtual ~MedioTwitter();

    // GETTERS
    
    virtual std::string getGrupoMedio();

    virtual medios::twitter::Cuenta * cuenta() const;

    uintmax_t id_ultima_publicacion() const;
    void id_ultima_publicacion(const uintmax_t & id_ultimo_tweet);

    // SETTERS

    virtual void cuenta(medios::twitter::Cuenta * cuenta_twitter);

    // METODOS

    virtual bool descargar_tweets(const medios::twitter::Aplicacion & app);

    virtual Medio * clonar();

    virtual std::string prefijoGrupo();

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IHashable

    virtual uintmax_t hashcode();

    // CONSULTAS

private:

    medios::twitter::Cuenta * cuenta_twitter;

    uintmax_t id_ultimo_tweet_analizado;
};
};
};

};

