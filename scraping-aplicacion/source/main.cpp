
// stl
#include <fstream>
#include <sstream>

#ifdef DEBUG || _DEBUG

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

void agregarNuevasCuentasDeTwitter()
{
    // recupero las cuentas de twitter.
    scraping::aplicacion::GestorMedios gestor_medios;
    gestor_medios.recuperarIDActualMedio();

    std::vector<scraping::twitter::modelo::Cuenta*> cuentas_twitter_existentes;
    gestor_medios.recuperar<scraping::twitter::modelo::Cuenta>(scraping::ConfiguracionScraping::prefijoTwitter(), cuentas_twitter_existentes);

    std::ifstream archivo_cuentas_a_agregar("cuentas_twitter_a_agregar.txt");
    std::ofstream archivo_cuentas_existentes("cuentas_twitter_existentes.txt", std::fstream::app);

    std::string linea;

    while (std::getline(archivo_cuentas_a_agregar, linea))
    {
        scraping::twitter::modelo::Cuenta * nueva_cuenta = new scraping::twitter::modelo::Cuenta(linea);

        if (gestor_medios.existeMedio<scraping::twitter::modelo::Cuenta>(cuentas_twitter_existentes, nueva_cuenta))
        {
            continue;
        }
        nueva_cuenta->asignarNuevoId();

        //gestor_medios.agregarCuentaDeTwitter(nueva_cuenta);
        gestor_medios.almacenarMedio(nueva_cuenta);
        gestor_medios.almacenarIDActualMedio();

        cuentas_twitter_existentes.push_back(nueva_cuenta);

        archivo_cuentas_existentes << linea << std::endl;
    }

    archivo_cuentas_a_agregar.close();
    archivo_cuentas_existentes.close();
    herramientas::utiles::FuncionesSistemaArchivos::eliminar("cuentas_twitter_a_agregar.txt");

    for (std::vector<scraping::twitter::modelo::Cuenta*>::iterator it = cuentas_twitter_existentes.begin(); it != cuentas_twitter_existentes.end(); it++)
    {
        delete *it;
    }
}

int main(int argc, char ** argv)
{
    // inicio la aplicacion y la config

    //scraping::ConfiguracionScraping::leerConfiguracion("config_scraping.json");

    //scraping::IAdministradorScraping::crearAdministradorScrapingLocal();
    scraping::IAdministradorScraping::iniciar("config_scraping.json");

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->abrirBD();
    scraping::IAdministradorScraping::getInstanciaAdminInfo()->recuperarIDsActuales();

    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->abrirBD();

    // agrego las nuevas cuentas de twitter a agregar.
    agregarNuevasCuentasDeTwitter();

    scraping::aplicacion::GestorTareas::scrapearTwitter();
    scraping::aplicacion::GestorTareas::depurarYAnalizarTwitter();
    scraping::aplicacion::GestorTareas::prepararYAlmacenarTwitter();

    // cierro la aplicacion
    scraping::IAdministradorScraping::getInstanciaAdminResultadosAnalisisDiario()->cerrarBD();

    scraping::IAdministradorScraping::getInstanciaAdminInfo()->almacenarIDsActuales();
    scraping::IAdministradorScraping::getInstanciaAdminInfo()->cerrarBD();

    scraping::IAdministradorScraping::liberar();

    // std::getchar();

    return 0;
}