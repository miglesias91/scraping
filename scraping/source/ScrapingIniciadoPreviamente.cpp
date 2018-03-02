#include <scraping/include/ScrapingIniciadoPreviamente.h>

using namespace scraping::excepciones;

ScrapingIniciadoPreviamente::ScrapingIniciadoPreviamente(std::string nombre_db) : Excepcion("Scraping ya fue iniciado.")
{
}

ScrapingIniciadoPreviamente::~ScrapingIniciadoPreviamente()
{
}
