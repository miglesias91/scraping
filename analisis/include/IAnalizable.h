#pragma once

// stl
#include <string>
#include <vector>

namespace scraping
{
namespace analisis
{

class IAnalizable
{
public:
    IAnalizable();
    virtual ~IAnalizable();

    // GETTERS

    virtual std::vector<std::string> getBolsaDePalabras() = 0;

    // SETTERS

    // METODOS

    // CONSULTAS
};

};
};
