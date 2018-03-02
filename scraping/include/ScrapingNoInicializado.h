#pragma once

// utiles
#include <utiles/include/Excepcion.h>

namespace scraping
{
namespace excepciones
{

class ScrapingNoInicializado : public herramientas::utiles::excepciones::Excepcion
{
public:
    ScrapingNoInicializado(std::string modulo = "");
    virtual ~ScrapingNoInicializado();
};

};
};

