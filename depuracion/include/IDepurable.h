#pragma once

// stl
#include <string>

namespace scraping
{
namespace depuracion
{

class IDepurable
{
public:
    IDepurable();
    virtual ~IDepurable();

    // GETTERS
    
    virtual std::string getTextoDepurable() = 0;

    // SETTERS

    // METODOS

    // CONSULTAS

};

};
};


