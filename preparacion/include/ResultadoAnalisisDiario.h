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


