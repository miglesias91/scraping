#pragma once


// log
#include <log/include/AdministradorLog.h>

// twitter
//#include <twitter/include/Tweet.h>

namespace scraping
{

class Logger
{
public:

    static void iniciar(const std::vector<std::string> & configs_logs);
    static void iniciar(const std::string & config_log);

    // GETTERS

    //static std::string getDebugLog(twitter::modelo::Tweet * tweet);

    // SETTERS

    // METODOS

    static void marca(const std::string & nombre_log, const std::string & mensaje);
    static void debug(const std::string & nombre_log, const std::string & mensaje);
    static void info(const std::string & nombre_log, const std::string & mensaje);
    static void advertencia(const std::string & nombre_log, const std::string & mensaje);
    static void error(const std::string & nombre_log, const std::string & mensaje);
    static void critico(const std::string & nombre_log, const std::string & mensaje);

protected:

private:

    Logger();
    virtual ~Logger();

    static std::unordered_map<std::string,herramientas::log::Logger*> logs;
    
};

};

