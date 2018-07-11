#include <scraping/include/Logger.h>

using namespace scraping;

// stl
#include <iostream>

std::unordered_map<std::string, herramientas::log::Logger*> Logger::logs;

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::iniciar(const std::vector<std::string> & configs_logs) {
    for(std::string config_log : configs_logs) {
        herramientas::log::Logger * log = herramientas::log::AdministradorLog::iniciarNuevo(config_log);
        logs[log->getNombre()] = log;
    }
}

void Logger::iniciar(const std::string & config_log) {
    herramientas::log::Logger * log = herramientas::log::AdministradorLog::iniciarNuevo(config_log);
    logs[log->getNombre()] = log;
}

void Logger::marca(const std::string & nombre_log, const std::string & mensaje) {
    logs[nombre_log]->marca(mensaje);
}

void Logger::debug(const std::string & nombre_log, const std::string & mensaje) {
    logs[nombre_log]->debug(mensaje);
}

void Logger::info(const std::string & nombre_log, const std::string & mensaje) {
    logs[nombre_log]->info(mensaje);
}

void Logger::advertencia(const std::string & nombre_log, const std::string & mensaje) {
    logs[nombre_log]->advertencia(mensaje);
}

void Logger::error(const std::string & nombre_log, const std::string & mensaje) {
    logs[nombre_log]->error(mensaje);
}

void Logger::critico(const std::string & nombre_log, const std::string & mensaje) {
    logs[nombre_log]->critico(mensaje);
}
