#pragma once

// utiles
#include <utiles/include/Excepcion.h>

namespace scraping
{
namespace excepciones
{

class ScrapingIniciadoPreviamente : public herramientas::utiles::excepciones::Excepcion
{
public:
    ScrapingIniciadoPreviamente(std::string nombre_db = "");
    virtual ~ScrapingIniciadoPreviamente();
};

};
};

