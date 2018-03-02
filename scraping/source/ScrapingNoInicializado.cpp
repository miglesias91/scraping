#include <scraping/include/ScrapingNoInicializado.h>

using namespace scraping::excepciones;

ScrapingNoInicializado::ScrapingNoInicializado(std::string modulo) : Excepcion(modulo + " no inicializado.")
{
}

ScrapingNoInicializado::~ScrapingNoInicializado()
{
}
