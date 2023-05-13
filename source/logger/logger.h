#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>

class Logger 
{
public:
    enum DBG_LVL {
        DEBUG=0,
        INFO=1,
        WARN=2,
        ERROR=3,
        FATAL=4
    };

    static Logger& get() {
        static Logger instance;
        return instance;
    }

    virtual ~Logger();
    
    static void debug(const char* tag, const char* format, ...);
    static void info(const char* tag, const char* format, ...);
    static void warn(const char* tag, const char* format, ...);
    static void error(const char* tag, const char* format, ...);
    static void fatal(const char* tag, const char* format, ...);

    DBG_LVL debugLevel();
    void setDebugLevel(DBG_LVL debugLevel);

private:
    Logger();
    DBG_LVL mDebugLvl;

    void log(const char* debugLevel, const char* tag, const char* format, va_list args);    
};

#endif // LOGGER_H