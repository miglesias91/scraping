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

    // getters de IAlmacenable

    virtual std::string getValorAlmacenable();

    // SETTERS

    // METODOS

    virtual void agregarMedio(ResultadoAnalisisMedio* resultado_medio);

    // metodos de IContieneJson

    virtual bool armarJson();

    virtual bool parsearJson();

    // metodos de IAlmacenable

    virtual void asignarNuevoId();

    virtual void parsearValorAlmacenable(std::string valor_almacenable);

    virtual std::string prefijoGrupo();
    // CONSULTAS

private:

    // ATRIBUTOS

    std::vector<ResultadoAnalisisMedio*> resultados_medios;
};

};
};


