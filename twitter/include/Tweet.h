#pragma once

// herramientas
#include <utiles/include/IContieneJson.h>
#include <utiles/include/Fecha.h>

namespace scraping
{
namespace twitter
{
namespace modelo
{

class Tweet : public herramientas::utiles::IContieneJson
{
public:

    Tweet(herramientas::utiles::Json * tweet_json = NULL);
	virtual ~Tweet();

    // GETTERS

    unsigned long long int getId();

    herramientas::utiles::Fecha getFechaCreacion();

    std::string getTexto();

    unsigned long long int getIdUsuario();

    std::vector<std::string> getHashtags();

    // SETTERS

    void setId(unsigned long long int id);

    void setFechaCreacion(herramientas::utiles::Fecha fecha_creacion);

    void setTexto(std::string texto);

    void setIdUsuario(unsigned long long int id_usuario);

    void setHashtags(std::vector<std::string> hashtags);

    // METODOS

    void agregarHashtags(std::string hashtag);

    // metodos de IContieneJson
    
    virtual bool armarJson();

    virtual bool parsearJson();

    // CONSULTAS

    bool contieneHashtag(std::string hashtag);

    // OPERADORES

private:

    // METODOS PRIVADOS

    herramientas::utiles::Fecha parsearFechaEnFormatoTwitter(std::string fecha_formato_twitter);

    // ATRIBUTOS

    unsigned long long int id;

    herramientas::utiles::Fecha fecha_creacion;

    // esta en formato UTF8 xq obtiene el valor del Json (rapidjson) que contiene.
    // (ir al test 'GettersYSettersCodificaciones' de 'herramientas_desarrollo' para ver como funciona.
    std::string texto;

    unsigned long long int id_usuario;

    std::vector<std::string> hashtags;
};

};
};
};


