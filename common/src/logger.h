//
// Created by Frityet on 2021-12-20.
//

#ifndef SOLARSYSTEM_COMMON_SERVER_LOGGER_
#define SOLARSYSTEM_COMMON_SERVER_LOGGER_

#include <stdio.h>

#include "utilities.h"

enum log_colour {
    LOG_COLOUR_INFO,
    LOG_COLOUR_DEBUG,
    LOG_COLOUR_WARNING,
    LOG_COLOUR_ERROR,
    LOG_COLOUR_FATAL
};

void initalise_logger(char *file);

void logbase(const char *msg, int line, const char *file, enum log_colour log_colour, FILE *stream);

#ifdef SOLARSYSTEM_COMMON_DEBUG
    #define LOG_INFO(...) { \
                        char _LOG_buf[4096]; \
                        sprintf(_LOG_buf, __VA_ARGS__);\
                        logbase(_LOG_buf, LINE_AND_FILE, LOG_COLOUR_INFO, stdout); \
                     } "FORCE_SEMICOLON"

    #define LOG_DEBUG(...) { \
                        char _LOG_buf[4096]; \
                        sprintf(_LOG_buf, __VA_ARGS__);\
                        logbase(_LOG_buf, LINE_AND_FILE, LOG_COLOUR_DEBUG, stdout); \
                     } "FORCE_SEMICOLON"

    #define LOG_WARNING(...) { \
                        char _LOG_buf[4096]; \
                        sprintf(_LOG_buf, __VA_ARGS__);\
                        logbase(_LOG_buf, LINE_AND_FILE, LOG_COLOUR_WARNING, stdout); \
                     } "FORCE_SEMICOLON"

    #define LOG_ERROR(...) { \
                        char _LOG_buf[4096]; \
                        sprintf(_LOG_buf, __VA_ARGS__); \
                        logbase(_LOG_buf, LINE_AND_FILE, LOG_COLOUR_ERROR, stderr); \
                     } "FORCE_SEMICOLON"

    #define LOG_FATAL(...) { \
                        char _LOG_buf[4096]; \
                        sprintf(_LOG_buf, __VA_ARGS__);                  \
                        logbase(_LOG_buf, LINE_AND_FILE, LOG_COLOUR_FATAL, stderr); \
                     } "FORCE_SEMICOLON"
#else
    #define LOG_INFO(...)   "FORCE_SEMICOLON"
    #define LOG_DEBUG(...)  "FORCE_SEMICOLON"
    #define LOG_WARNING(...)"FORCE_SEMICOLON"
    #define LOG_ERROR(...)  "FORCE_SEMICOLON"
    #define LOG_FATAL(...)  "FORCE_SEMICOLON"
#endif


#endif //SOLARSYSTEM_COMMON_SERVER_LOGGER_
