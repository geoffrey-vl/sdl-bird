#include "logger.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

Logger::Logger()
{
    mDebugLvl = Logger::DBG_LVL::DEBUG;
}

Logger::~Logger()
{
}

Logger::DBG_LVL Logger::debugLevel()
{
    return mDebugLvl;
}

void Logger::setDebugLevel(Logger::DBG_LVL debugLevel)
{
    mDebugLvl = debugLevel;
}

void Logger::debug(const char* tag, const char* format, ...) //the ... ("ellipsis") argument
{
    Logger& logger = Logger::get();
    if(Logger::get().debugLevel() > Logger::DBG_LVL::DEBUG)
        return;
    va_list arglist;
    va_start( arglist, format );
    logger.log("[DEBUG] ",tag, format, arglist);
    va_end( arglist );
}

void Logger::info(const char* tag, const char* format, ...)
{
    Logger& logger = Logger::get();
    if(logger.debugLevel() > Logger::DBG_LVL::INFO)
        return;
    va_list arglist;
    va_start( arglist, format );
    logger.log("[INFO] ", tag, format, arglist);
    va_end( arglist );
}

void Logger::warn(const char* tag, const char* format, ...)
{
    Logger& logger = Logger::get();
    if(logger.debugLevel() > Logger::DBG_LVL::WARN)
        return;
    va_list arglist;
    va_start( arglist, format );
    logger.log("[WARN] ", tag, format, arglist);
    va_end( arglist );
}

void Logger::error(const char* tag, const char* format, ...)
{
    Logger& logger = Logger::get();
    if(logger.debugLevel() > Logger::DBG_LVL::ERROR)
        return;
    va_list arglist;
    va_start( arglist, format );
    logger.log("[ERROR] ", tag, format, arglist);
    va_end( arglist );
}

void Logger::fatal(const char* tag, const char* format, ...)
{
    Logger& logger = Logger::get();
    va_list arglist;
    va_start( arglist, format );
    logger.log("[FATAL] ", tag, format, arglist);
    va_end( arglist );
    exit(1);
}


void Logger::log(const char* debugLevel, const char* tag, const char* format, va_list args) 
{   
    uint16_t sz = ((unsigned)strlen(debugLevel))+((unsigned)strlen(tag))+3+((unsigned)strlen(format))+1+1;
    char concat[sz];
    strcpy(concat, debugLevel);
    strcpy(concat, tag);
    strcat(concat, " - "); 
    strcat(concat, format); 
    strcat(concat, "\n"); 

    vprintf( concat, args );
    fflush(stdout);
}