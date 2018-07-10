
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

// scraping
#include <scraping/include/IAdministradorScraping.h>
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorTareas.h>

// extraccion
#include <extraccion/include/MedioTwitter.h>
#include <extraccion/include/MedioFacebook.h>

void agregar_nuevos_medios(const std::string & path_json) {

    if (false == std::experimental::filesystem::exists(path_json)) {
        return;
    }

    std::string contenido_json = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer(path_json, contenido_json);

    herramientas::utiles::Json json(contenido_json);

    std::vector<scraping::extraccion::Medio*> medios;

    if(json.contieneAtributo("twitter")) {
        std::vector<herramientas::utiles::Json*> json_twitters = json.getAtributoArrayJson("twitter");
        std::for_each(json_twitters.begin(), json_twitters.end(), [=, &medios](herramientas::utiles::Json * json_twitter) {
            uintmax_t id = json_twitter->getAtributoValorUint("id");
            std::string nombre_cuenta = json_twitter->getAtributoValorString("cuenta");

            scraping::extraccion::interfaceo::MedioTwitter * nueva_cuenta = new scraping::extraccion::interfaceo::MedioTwitter(nombre_cuenta);
            nueva_cuenta->setId(new herramientas::utiles::ID(id));

            medios.push_back(nueva_cuenta);

            delete json_twitter;
        });
    }

    if(json.contieneAtributo("facebook")) {
        std::vector<herramientas::utiles::Json*> json_facebooks = json.getAtributoArrayJson("facebook");
        std::for_each(json_facebooks.begin(), json_facebooks.end(), [=, &medios](herramientas::utiles::Json * json_facebook) {
            uintmax_t id = json_facebook->getAtributoValorUint("id");
            std::string nombre_pagina = json_facebook->getAtributoValorString("pagina");

            scraping::extraccion::interfaceo::MedioFacebook * nueva_pagina = new scraping::extraccion::interfaceo::MedioFacebook(nombre_pagina);
            nueva_pagina->setId(new herramientas::utiles::ID(id));

            medios.push_back(nueva_pagina);

            delete json_facebook;
        });
    }

    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.almacenar(medios);

    std::for_each(medios.begin(), medios.end(), [=](scraping::extraccion::Medio * medio) { delete medio; });

    std::experimental::filesystem::remove(path_json);
}

int main(int argc, char ** argv)
{
    // inicio la aplicacion y la config
    scraping::IAdministradorScraping::iniciar("config_scraping.json");

    scraping::IAdministradorScraping::getInstanciaAdminInfoTemporal()->abrirBD();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->abrirBD();
    scraping::IAdministradorScraping::getInstanciaAdminResultadosDiarios()->recuperarIDsActuales();

    // agrego nuevos medios
    agregar_nuevos_medios("nuevos_medios.json");

    // scrapeo
    scraping::Logger::info("lanzo scraping twitter.");
    std::future<void> tarea_twitter = std::async(std::launch::async, [=]() { scraping::aplicacion::GestorTareas::scrapear_twitter(); });
    scraping::Logger::info("lanzo scraping facebook.");
    std::future<void> tarea_facebook = std::async(std::launch::async, [=]() { scraping::aplicacion::GestorTareas::scrapear_facebook(); });
    scraping::Logger::info("lanzo scraping portales.");
    std::future<void> tarea_portales = std::async(std::launch::async, [=]() { scraping::aplicacion::GestorTareas::scrapear_portales(); });

    tarea_twitter.wait();
    tarea_facebook.wait();
    tarea_portales.wait();
    scraping::Logger::info("scrapeo terminado.");

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