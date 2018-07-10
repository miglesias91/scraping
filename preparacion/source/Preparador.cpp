#include <preparacion/include/Preparador.h>

// scraping
#include <scraping/include/ConfiguracionScraping.h>
#include <scraping/include/GestorMedios.h>
#include <scraping/include/GestorAnalisisDiario.h>

// analisis
#include <analisis/include/ResultadoAnalisis.h>

// extraccion
//#include <extraccion/include/MedioFacebook.h>
//#include <extraccion/include/MedioTwitter.h>
//#include <extraccion/include/MedioPortalNoticias.h>

// preparacion
#include <preparacion/include/ResultadoAnalisisContenido.h>
#include <preparacion/include/ResultadoAnalisisMedio.h>
#include <preparacion/include/ResultadoAnalisisDiario.h>

using namespace scraping::preparacion;

std::mutex Preparador::mutex_modificacion_resultado_diario;

Preparador::Preparador() {}

Preparador::~Preparador() {}

// GETTERS

// SETTERS

// METODOS

bool Preparador::preparar(scraping::extraccion::Medio * medio) const {
    std::vector<std::pair<std::string, std::vector<uintmax_t>>> ids_para_preparar;
    medio->ids_para_preparar(&ids_para_preparar);

    scraping::aplicacion::GestorAnalisisDiario gestor_analisis;
    scraping::aplicacion::GestorMedios gestor_medios;
    std::for_each(ids_para_preparar.begin(), ids_para_preparar.end(), [=](std::pair<std::string, std::vector<uintmax_t>> fecha_ids) {

        std::unordered_map<std::string, std::vector<analisis::ResultadoAnalisis*>> resultados_por_categoria_fecha;  // map<categoria, contenidos>
        std::for_each(fecha_ids.second.begin(), fecha_ids.second.end(), [=, &resultados_por_categoria_fecha](uintmax_t id) {  // recupero los resultados de la fecha

            preparacion::ResultadoAnalisisContenido * resultado_contenido = new preparacion::ResultadoAnalisisContenido();
            resultado_contenido->setId(new herramientas::utiles::ID(id));

            gestor_analisis.recuperarResultadoAnalisis(resultado_contenido);

            (&resultados_por_categoria_fecha[resultado_contenido->categoria()])->push_back(resultado_contenido);
        });

        preparacion::ResultadoAnalisisMedio * resultado_por_fecha = new preparacion::ResultadoAnalisisMedio();
        resultado_por_fecha->setId(medio->getId()->copia());
        std::for_each(resultados_por_categoria_fecha.begin(), resultados_por_categoria_fecha.end(),
            [=, &resultado_por_fecha](std::pair<std::string, std::vector<analisis::ResultadoAnalisis*>> categoria_resultados) {

            preparacion::ResultadoAnalisisContenido * resultado_categoria = new preparacion::ResultadoAnalisisContenido();
            this->combinar(categoria_resultados.second, resultado_categoria);
            resultado_por_fecha->set_resultado_de_categoria(categoria_resultados.first, resultado_categoria);

            std::for_each(categoria_resultados.second.begin(), categoria_resultados.second.end(), [=](analisis::ResultadoAnalisis * resultado) { delete resultado; });
        });

        preparacion::ResultadoAnalisisDiario resultado_diario;
        resultado_diario.setId(new herramientas::utiles::ID(std::stoul(fecha_ids.first)));

        mutex_modificacion_resultado_diario.lock();
        gestor_analisis.recuperarResultadoAnalisisDiario(&resultado_diario);  // recupero resultado diario para la fecha en cuestion,
        resultado_diario.agregarResultadoDeMedio(resultado_por_fecha);  // agrego los resultados del medio y
        gestor_analisis.almacenarResultadoAnalisisDiario(&resultado_diario);  // almaceno el resultado diario actualizado con la info del medio.
        mutex_modificacion_resultado_diario.unlock();

        medio->contenidos_preparados(fecha_ids.first, fecha_ids.second);
        gestor_medios.actualizarMedio(medio);

        delete resultado_por_fecha;
    });

    return true;
}

bool Preparador::combinar(std::vector<scraping::analisis::ResultadoAnalisis*> resultados_a_combinar, scraping::analisis::ResultadoAnalisis * resultado_combinacion) const {
    unsigned int cantidad_de_fuerzas_sumadas = 0;
    for (std::vector<analisis::ResultadoAnalisis*>::iterator it = resultados_a_combinar.begin(); it != resultados_a_combinar.end(); it++)
    {
        resultado_combinacion->combinarCon(*it);
    }

    return true;
}

// CONSULTAS