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

    static void iniciar(std::string config_log);

    // GETTERS

    //static std::string getDebugLog(twitter::modelo::Tweet * tweet);

    // SETTERS

    // METODOS

    static void marca(std::string mensaje);
    static void debug(std::string mensaje);
    static void info(std::string mensaje);
    static void advertencia(std::string mensaje);
    static void error(std::string mensaje);
    static void critico(std::string mensaje);

protected:

private:

    Logger();
    virtual ~Logger();

    static herramientas::log::Logger * log;
    
};

};

