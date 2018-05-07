#pragma once

// extraccion
#include <extraccion/include/Medio.h>

// analisis
#include <analisis/include/ResultadoAnalisis.h>

// twitter
#include <twitter/include/Cuenta.h>

namespace scraping
{
namespace aplicacion
{

class GestorTareas
{
public:
    GestorTareas();
    virtual ~GestorTareas();

    struct resultados_agrupados_por_medio
    {
        extraccion::Medio * medio;
        std::vector<analisis::ResultadoAnalisis*> resultados;
    };

    // GETTES

    // SETTER

    // METODOS

    // twitter
    static void scrapearTwitter();

    static void depurarYAnalizarTwitter();

    static void prepararYAlmacenarTwitter();

    // facebook
    static void scrapearFacebook();

    static void depurarYAnalizarFacebook();

    static void prepararYAlmacenarFacebook();

    // general

    static void depurarYAnalizarContenidos();
    
    static void prepararYAlmacenarContenidos();

    // CONSULTAS

private:

    static void agruparResultadosDeMediosPorFecha(std::unordered_map<std::string, std::vector<resultados_agrupados_por_medio>> * mapa_resultados_por_fecha);
    

};

};
};