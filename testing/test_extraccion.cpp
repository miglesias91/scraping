// catch2
#include <catch.hpp>

// medios
//#include <twitter/include/Aplicacion.h>
//#include <twitter/include/Cuenta.h>
//#include <twitter/include/Tweet.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/IAdministradorScraping.h>

// extraccion
#include <extraccion/include/MedioTwitter.h>
#include <extraccion/include/MedioFacebook.h>
#include <extraccion/include/Contenido.h>

TEST_CASE("almacenar_y_recuperar_correctamente_medio_twitter", "extraccion")
{
    //// probar almacenar y recuperar una cuenta de twitter como Medio, y los tweets como Contenidos.
    //// agregarles los Tweets leidos desde disco. a partir de ahi hacer que se almacene el Medio (1 registro) y los Contenidos (1 registro por cada medio),
    //// y que despues se puedan acceder tanto el Medio como los Contenidos por separados.

    scraping::extraccion::Medio::getGestorIDs()->setIdActual(100);
    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(200);

    scraping::extraccion::interfaceo::MedioTwitter cuenta("clarin");
    cuenta.asignarNuevoId();

    scraping::extraccion::Contenido * contenido1 = new scraping::extraccion::Contenido("titulo1", "texto1", "categoria1", herramientas::utiles::Fecha::getFechaActual());
    contenido1->asignarNuevoId();

    cuenta.agregarContenidoParaAnalizar(contenido1);

    scraping::extraccion::Contenido * contenido2 = new scraping::extraccion::Contenido("titulo2", "texto2", "categoria2", herramientas::utiles::Fecha::getFechaActual());
    contenido2->asignarNuevoId();

    cuenta.agregarContenidoParaAnalizar(contenido2);

    std::vector<unsigned long long int> ids_tweets = cuenta.getIDsContenidosNoAnalizados();

    REQUIRE(100 == cuenta.getId()->numero());

    REQUIRE(200 == ids_tweets[0]);
    REQUIRE(201 == ids_tweets[1]);

    // almaceno el medio (cuenta twitter).
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&cuenta);

    // almaceno contenidos
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(contenido1);
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(contenido2);

    // recupero el medio.
    scraping::extraccion::interfaceo::MedioTwitter cuenta_recuperada;
    cuenta_recuperada.setId(cuenta.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&cuenta_recuperada);

    // recupero los contenidos del medio.
    scraping::extraccion::Contenido contenido_recuperado1;
    contenido_recuperado1.setId(contenido1->getId()->copia());
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&contenido_recuperado1);

    scraping::extraccion::Contenido contenido_recuperado2;
    contenido_recuperado2.setId(contenido2->getId()->copia());
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&contenido_recuperado2);

    REQUIRE(cuenta.cuenta()->getNombre() == cuenta_recuperada.cuenta()->getNombre());

    REQUIRE(contenido1->getTitulo() == contenido_recuperado1.getTitulo());
    REQUIRE(contenido2->getTitulo() == contenido_recuperado2.getTitulo());

    REQUIRE(contenido1->getTexto() == contenido_recuperado1.getTexto());
    REQUIRE(contenido2->getTexto() == contenido_recuperado2.getTexto());

    REQUIRE(true == (contenido1->getFecha() == contenido_recuperado1.getFecha()));
    REQUIRE(true == (contenido2->getFecha() == contenido_recuperado2.getFecha()));

    delete contenido1;
    delete contenido2;
}


TEST_CASE("almacenar_y_recuperar_correctamente_medio_facebook", "extraccion")
{
    //// probar almacenar y recuperar una cuenta de twitter como Medio, y los tweets como Contenidos.
    //// agregarles los Tweets leidos desde disco. a partir de ahi hacer que se almacene el Medio (1 registro) y los Contenidos (1 registro por cada medio),
    //// y que despues se puedan acceder tanto el Medio como los Contenidos por separados.

    scraping::extraccion::Medio::getGestorIDs()->setIdActual(100);
    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(200);

    scraping::extraccion::interfaceo::MedioFacebook pagina("clarin");
    pagina.asignarNuevoId();

    scraping::extraccion::Contenido * contenido1 = new scraping::extraccion::Contenido("titulo1", "texto1", "categoria1", herramientas::utiles::Fecha::getFechaActual());
    contenido1->asignarNuevoId();

    pagina.agregarContenidoParaAnalizar(contenido1);

    scraping::extraccion::Contenido * contenido2 = new scraping::extraccion::Contenido("titulo2", "texto2", "categoria2", herramientas::utiles::Fecha::getFechaActual());
    contenido2->asignarNuevoId();

    pagina.agregarContenidoParaAnalizar(contenido2);

    std::vector<unsigned long long int> ids_publicaciones = pagina.getIDsContenidosNoAnalizados();

    REQUIRE(100 == pagina.getId()->numero());

    REQUIRE(200 == ids_publicaciones[0]);
    REQUIRE(201 == ids_publicaciones[1]);

    // almaceno el medio (cuenta twitter).
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(&pagina);

    // almaceno contenidos
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(contenido1);
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->almacenar(contenido2);

    // recupero el medio.
    scraping::extraccion::interfaceo::MedioFacebook pagina_recuperada;
    pagina_recuperada.setId(pagina.getId()->copia());

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&pagina_recuperada);

    // recupero los contenidos del medio.
    scraping::extraccion::Contenido contenido_recuperado1;
    contenido_recuperado1.setId(contenido1->getId()->copia());
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&contenido_recuperado1);

    scraping::extraccion::Contenido contenido_recuperado2;
    contenido_recuperado2.setId(contenido2->getId()->copia());
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->recuperar(&contenido_recuperado2);

    REQUIRE(pagina.pagina()->getNombre() == pagina_recuperada.pagina()->getNombre());

    REQUIRE(contenido1->getTitulo() == contenido_recuperado1.getTitulo());
    REQUIRE(contenido2->getTitulo() == contenido_recuperado2.getTitulo());

    REQUIRE(contenido1->getTexto() == contenido_recuperado1.getTexto());
    REQUIRE(contenido2->getTexto() == contenido_recuperado2.getTexto());

    REQUIRE(true == (contenido1->getFecha() == contenido_recuperado1.getFecha()));
    REQUIRE(true == (contenido2->getFecha() == contenido_recuperado2.getFecha()));

    delete contenido1;
    delete contenido2;
}