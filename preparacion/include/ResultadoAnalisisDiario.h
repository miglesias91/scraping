#pragma once

// preparacion
#include <preparacion/include/ResultadoAnalisisMedio.h>

namespace scraping
{
namespace preparacion
{

class ResultadoAnalisisDiario : public scraping::IAlmacenable, public herramientas::utiles::IContieneJson
{
public:

    ResultadoAnalisisDiario();

    virtual ~ResultadoAnalisisDiario();

    // GETTERS

    virtual herramientas::utiles::Json * getRegistroAExportar();

    virtual ResultadoAnalisisMedio * getResultadoMedio(unsigned long long int id_medio);

    static herramientas::utiles::ID getIDDiario();

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    // METODOS

    // filtra medios y terminos.
    // (es decir, elimina todos los medios que no esten incluidos en los ids pasados parametro
    // y todos los terminos que no esten incluidos en las palabras pasadas por parametro).
    // los terminos a filtrar ACEPTAN COMODINES ('*' al final de la palabra).
    virtual void filtrar(const std::vector<unsigned long long int> & ids_medios_a_filtrar, const std::vector<std::string> & terminos_a_filtrar = {});

    // ResultadoAnalisisDiario NO SE ENCARGAR DE ELIMINAR la memoria del "resultado_medio" pasado por parametro.
    // Es decir que "resultado_medio" se debe eliminar luego de ser usado por esta funcion (a menos que se siga utilizando).
    virtual void agregarResultadoDeMedio(ResultadoAnalisisMedio* resultado_medio);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();

    // CONSULTAS
    bool existeResultadoDeMedio(unsigned long long int id_medio);

private:

    // ATRIBUTOS

    std::unordered_map<unsigned long long int, ResultadoAnalisisMedio*> resultados_medios;
};

};
};


