#pragma once

// utiles
#include <utiles/include/Excepcion.h>

namespace scraping
{
namespace excepciones
{

class PrefijoDeMedioNoSeteado : public herramientas::utiles::excepciones::Excepcion
{
public:
    PrefijoDeMedioNoSeteado();
    virtual ~PrefijoDeMedioNoSeteado();
};

};
};

