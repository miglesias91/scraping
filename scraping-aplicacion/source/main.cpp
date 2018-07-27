
// stl
#include <fstream>
#include <sstream>
#include <future>
#include <filesystem>

#if  defined(DEBUG) || defined(_DEBUG)

// vld
#include <vld.h>

#endif // DEBUG || _DEBUG

// herramientas
#include <utiles/include/FuncionesSistemaArchivos.h>

// noticias
#include <noticias/include/fabrica_portales.h>

// scraping
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorTareas.h>

// extraccion
#include <extraccion/include/MedioTwitter.h>
#include <extraccion/include/MedioFacebook.h>
#include <extraccion/include/MedioPortalNoticias.h>

void registrar_abms() {
    std::vector<scraping::extraccion::Medio*> alta_de_medios;
    std::vector<scraping::extraccion::Medio*> baja_de_medios;
    for (auto abm : std::experimental::filesystem::directory_iterator(scraping::ConfiguracionScraping::dirABMs())) {

        std::string contenido_json = "";
        herramientas::utiles::FuncionesSistemaArchivos::leer(abm.path().string(), contenido_json);

        herramientas::utiles::Json json(contenido_json);

        if(json.contieneAtributo("twitter")) {
            herramientas::utiles::Json* json_twitter = json.getAtributoValorJson("twitter");

            std::vector<herramientas::utiles::Json*> json_altas_twitter = json_twitter->getAtributoArrayJson("altas");
            std::for_each(json_altas_twitter.begin(), json_altas_twitter.end(), [=, &alta_de_medios](herramientas::utiles::Json * json_twitter) {
                uintmax_t id = json_twitter->getAtributoValorUint("id");
                std::string nombre_cuenta = json_twitter->getAtributoValorString("usuario");

                scraping::extraccion::interfaceo::MedioTwitter * nueva_cuenta = new scraping::extraccion::interfaceo::MedioTwitter(nombre_cuenta);
                nueva_cuenta->setId(new herramientas::utiles::ID(id));

                alta_de_medios.push_back(nueva_cuenta);

                scraping::Logger::info("scraping", "cuenta de twitter '" + nueva_cuenta->cuenta()->getNombre() + "' agregada.");

                delete json_twitter;
            });

            std::vector<uintmax_t> json_bajas_twitter = json_twitter->getAtributoArrayUint("bajas");
            std::for_each(json_bajas_twitter.begin(), json_bajas_twitter.end(), [=, &baja_de_medios](uintmax_t id_twitter) {

                scraping::extraccion::interfaceo::MedioTwitter * nueva_cuenta = new scraping::extraccion::interfaceo::MedioTwitter();
                nueva_cuenta->setId(new herramientas::utiles::ID(id_twitter));

                baja_de_medios.push_back(nueva_cuenta);

                scraping::Logger::info("scraping", "cuenta de twitter '" + std::to_string(id_twitter) + "' eliminada.");
            });
            delete json_twitter;
        }

        if(json.contieneAtributo("facebook")) {
            herramientas::utiles::Json* json_facebook = json.getAtributoValorJson("facebook");

            std::vector<herramientas::utiles::Json*> json_altas_facebook = json_facebook->getAtributoArrayJson("altas");
            std::for_each(json_altas_facebook.begin(), json_altas_facebook.end(), [=, &alta_de_medios](herramientas::utiles::Json * json_facebook) {
                uintmax_t id = json_facebook->getAtributoValorUint("id");
                std::string nombre_pagina = json_facebook->getAtributoValorString("usuario");

                scraping::extraccion::interfaceo::MedioFacebook * nueva_pagina = new scraping::extraccion::interfaceo::MedioFacebook(nombre_pagina);
                nueva_pagina->setId(new herramientas::utiles::ID(id));

                alta_de_medios.push_back(nueva_pagina);

                scraping::Logger::info("scraping", "cuenta de facebook '" + nueva_pagina->pagina()->getNombre() + "' agregada.");

                delete json_facebook;
            });

            std::vector<uintmax_t> json_bajas_facebook = json_facebook->getAtributoArrayUint("bajas");
            std::for_each(json_bajas_facebook.begin(), json_bajas_facebook.end(), [=, &baja_de_medios](uintmax_t id_facebook) {
                scraping::extraccion::interfaceo::MedioFacebook * nueva_pagina = new scraping::extraccion::interfaceo::MedioFacebook();
                nueva_pagina->setId(new herramientas::utiles::ID(id_facebook));

                baja_de_medios.push_back(nueva_pagina);

                scraping::Logger::info("scraping", "cuenta de facebook '" + std::to_string(id_facebook) + "' eliminada.");

                delete json_facebook;
            });
            delete json_facebook;
        }

        if(json.contieneAtributo("portales")) {
            herramientas::utiles::Json* json_portales = json.getAtributoValorJson("portales");

            std::vector<herramientas::utiles::Json*> json_altas_portales = json_portales->getAtributoArrayJson("altas");
            std::for_each(json_altas_portales.begin(), json_altas_portales.end(), [=, &alta_de_medios](herramientas::utiles::Json * json_portal) {
                uintmax_t id = json_portal->getAtributoValorUint("id");
                std::string web_portal = json_portal->getAtributoValorString("web");

                scraping::extraccion::interfaceo::MedioPortalNoticias * nuevo_portal = new scraping::extraccion::interfaceo::MedioPortalNoticias(medios::noticias::fabrica_portales::nuevo(web_portal));
                nuevo_portal->setId(new herramientas::utiles::ID(id));

                alta_de_medios.push_back(nuevo_portal);

                scraping::Logger::info("scraping", "portal de noticias '" + nuevo_portal->portal()->web() + "' agregada.");

                delete json_portal;
            });
            delete json_portales;
        }

        std::experimental::filesystem::remove(abm);
    }

    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.almacenar_ya(alta_de_medios);
    gestor_medios.eliminar_ya(baja_de_medios);

    std::for_each(alta_de_medios.begin(), alta_de_medios.end(), [=](scraping::extraccion::Medio * medio) { delete medio; });
    std::for_each(baja_de_medios.begin(), baja_de_medios.end(), [=](scraping::extraccion::Medio * medio) { delete medio; });
}

int main(int argc, char ** argv)
{
    // inicio la aplicacion y la config
    scraping::IAdministradorScraping::iniciar("config_scraping.json");

    scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->abrirBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->abrirBD();
    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperarIDsActuales();

    // agrego nuevos medios
    registrar_abms();

    // scrapeo
    scraping::Logger::info("scraping", "lanzo scraping twitter.");
    std::future<void> tarea_twitter = std::async(std::launch::async, [=]() { scraping::aplicacion::GestorTareas::scrapear_twitter(); });
    scraping::Logger::info("scraping", "lanzo scraping facebook.");
    std::future<void> tarea_facebook = std::async(std::launch::async, [=]() { scraping::aplicacion::GestorTareas::scrapear_facebook(); });
    scraping::Logger::info("scraping", "lanzo scraping portales.");
    std::future<void> tarea_portales = std::async(std::launch::async, [=]() { scraping::aplicacion::GestorTareas::scrapear_portales(); });

    tarea_twitter.wait();
    tarea_facebook.wait();
    tarea_portales.wait();
    scraping::Logger::info("scraping", "scrapeo terminado.");

    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->guardar_checkpoint();

    // cierro la aplicacion
    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenarIDActual<scraping::extraccion::Medio>();

    scraping::extraccion::Contenido::getGestorIDs()->setIdActual(0);  // reseteo el id de contenidos actual,
    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->almacenarIDActual<scraping::extraccion::Contenido>();  // y lo guardo.
    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->cerrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->cerrarBD();

    scraping::IAdministradorScraping::liberar();

    return 0;
}