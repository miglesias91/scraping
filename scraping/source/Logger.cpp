#include <scraping/include/Logger.h>

using namespace scraping;

// stl
#include <iostream>

herramientas::log::Logger * Logger::log = nullptr;

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::iniciar(std::string config_log)
{
    log = herramientas::log::AdministradorLog::iniciarNuevo(config_log);
}

//std::string Logger::getDebugLog(twitter::modelo::Tweet * tweet)
//{
//    tweet->armarJson();
// 
//    return tweet->getJson()->jsonString();
//}

void Logger::marca(std::string mensaje)
{
    log->marca(mensaje);
}

void Logger::debug(std::string mensaje)
{
    log->debug(mensaje);
}

void Logger::info(std::string mensaje)
{
    log->info(mensaje);
}

void Logger::advertencia(std::string mensaje)
{
    log->advertencia(mensaje);
}

void Logger::error(std::string mensaje)
{
    log->error(mensaje);
}

void Logger::critico(std::string mensaje)
{
    log->critico(mensaje);
}
