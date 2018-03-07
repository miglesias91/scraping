// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>
#include <sstream>

// scraping
#include <scraping/include/IAdministradorScraping.h>

// facebook
#include <facebook/include/Aplicacion.h>
#include <facebook/include/Pagina.h>
#include <facebook/include/Publicacion.h>

// herramenitas
#include <utiles/include/Json.h>
#include <utiles/include/Conversiones.h>

using namespace scraping::facebook;

TEST(ScrapingFacebook, obtenerUltimasPublicaciones)
{
    scraping::facebook::ConsumidorAPI * consumidor_api_facebook = new scraping::facebook::ConsumidorAPI("929798640478438", "f36e906bf6b8445ac3ee53e95ac303a7");

    scraping::facebook::modelo::Aplicacion app(consumidor_api_facebook);

    scraping::facebook::modelo::Pagina tn("todo-noticias");

    std::vector<scraping::facebook::modelo::Publicacion*> tweets = app.leerUltimasPublicaciones(&tn);

    ASSERT_EQ(true, true);
}

TEST(ScrapingFacebook, parsearPublicacionesCorrectamente)
{
    std::ifstream archivo_tweets("publicaciones_de_prueba.txt");

    std::stringstream sstream;
    sstream << archivo_tweets.rdbuf();

    std::string string_tweets(sstream.str());

    herramientas::utiles::Json json_publicaciones(string_tweets);

    std::vector<herramientas::utiles::Json*> publicaciones_json = json_publicaciones.getAtributoArrayJson("data");

    std::vector<modelo::Publicacion*> publicaciones;
    modelo::Publicacion* nueva_publicacion = NULL;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++)
    {
        nueva_publicacion = new modelo::Publicacion(*it);
        publicaciones.push_back(nueva_publicacion);
    }

    unsigned long long int id_parseado_publicacion_1 = publicaciones[0]->getIdPublicacion();
    unsigned long long int id_parseado_pagina_1 = publicaciones[0]->getIdPagina();
    std::string texto_parseado_publicacion_1 = publicaciones[0]->getTexto();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_publicacion_1 = publicaciones[0]->getFechaCreacion();

    unsigned long long int id_correcto_publicacion_1 = 522759367889906;
    unsigned long long int id_correcto_pagina_1 = 116053261893854;
    std::string texto_correcto_publicacion_1 = "HISTÓRICO: La ONU aprobó la iniciativa argentina sobre el marco legal para la reestructuración de deuda. #SoberaníaEconómica.";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_publicacion_1(10, 9, 2015, 20, 33, 54);

    for (std::vector<modelo::Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); it++)
    {
        delete *it;
    }

    ASSERT_EQ(id_correcto_publicacion_1, id_parseado_publicacion_1);
    ASSERT_STREQ(texto_correcto_publicacion_1.c_str(), texto_parseado_publicacion_1.c_str());
    ASSERT_EQ(true, fecha_de_creacion_correcta_publicacion_1 == fecha_de_creacion_parseada_publicacion_1);
    ASSERT_EQ(id_correcto_pagina_1, id_parseado_pagina_1);
}


TEST(ScrapingFacebook, almacenarYRecuperarPublicacionesCorrectamente)
{
    std::ifstream archivo_tweets("publicaciones_de_prueba.txt");

    std::stringstream sstream;
    sstream << archivo_tweets.rdbuf();

    std::string string_tweets(sstream.str());

    herramientas::utiles::Json json_publicaciones(string_tweets);

    std::vector<herramientas::utiles::Json*> publicaciones_json = json_publicaciones.getAtributoArrayJson("data");

    std::vector<modelo::Publicacion*> publicaciones;
    modelo::Publicacion* nueva_publicacion = NULL;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++)
    {
        nueva_publicacion = new modelo::Publicacion(*it);
        publicaciones.push_back(nueva_publicacion);
    }

    publicaciones[0]->asignarNuevoId();
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(publicaciones[0]);

    modelo::Publicacion * publicacion_recuperada = new modelo::Publicacion();
    publicacion_recuperada->setId(publicaciones[0]->getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(publicacion_recuperada);

    unsigned long long int id_parseado_publicacion_1 = publicacion_recuperada->getIdPublicacion();
    unsigned long long int id_parseado_pagina_1 = publicacion_recuperada->getIdPagina();
    std::string texto_parseado_publicacion_1 = publicacion_recuperada->getTexto();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_publicacion_1 = publicacion_recuperada->getFechaCreacion();

    unsigned long long int id_correcto_publicacion_1 = 522759367889906;
    unsigned long long int id_correcto_pagina_1 = 116053261893854;
    std::string texto_correcto_publicacion_1 = "HISTÓRICO: La ONU aprobó la iniciativa argentina sobre el marco legal para la reestructuración de deuda. #SoberaníaEconómica.";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_publicacion_1(10, 9, 2015, 20, 33, 54);

    for (std::vector<modelo::Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); it++)
    {
        delete *it;
    }

    delete publicacion_recuperada;

    ASSERT_EQ(id_correcto_publicacion_1, id_parseado_publicacion_1);
    ASSERT_STREQ(texto_correcto_publicacion_1.c_str(), texto_parseado_publicacion_1.c_str());
    ASSERT_EQ(true, fecha_de_creacion_correcta_publicacion_1 == fecha_de_creacion_parseada_publicacion_1);
    ASSERT_EQ(id_correcto_pagina_1, id_parseado_pagina_1);
}