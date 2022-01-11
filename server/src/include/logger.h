//
// Created by Frityet on 2021-12-20.
//

#ifndef UNIGS_SERVER_LOGGER_
#define UNIGS_SERVER_LOGGER_

#include <stdio.h>

#include "common.h"

enum log_colour {
    LOG_COLOUR_INFO,
    LOG_COLOUR_DEBUG,
    LOG_COLOUR_WARNING,
    LOG_COLOUR_ERROR,
    LOG_COLOUR_FATAL
};

void initalise_logger(char *file);

void logbase(const char *msg, enum log_colour log_colour, FILE *stream);



#define LOG_INFO(...) { \
                    char _LOG_buf[4096]; \
                    printf("["__FILE__":%d] ", __LINE__); \
                    sprintf(_LOG_buf, __VA_ARGS__);                  \
                    logbase(_LOG_buf, LOG_COLOUR_INFO, stdout);\
                 } "FORCE_SEMICOLON"

#define LOG_DEBUG(...) { \
                    char _LOG_buf[4096];   \
                    sprintf(_LOG_buf, __VA_ARGS__);      \
                    logbase(_LOG_buf, LOG_COLOUR_DEBUG, stdout); \
                 } "FORCE_SEMICOLON"

#define LOG_WARNING(...) { \
                    char _LOG_buf[4096]; \
                    sprintf(_LOG_buf, __VA_ARGS__);\
                    logbase(_LOG_buf, LOG_COLOUR_WARNING, stdout);\
                 } "FORCE_SEMICOLON"

#define LOG_ERROR(...) { \
                    char _LOG_buf[4096]; \
                    sprintf(_LOG_buf, __VA_ARGS__);\
                    logbase(_LOG_buf, LOG_COLOUR_ERROR, stderr);\
                 } "FORCE_SEMICOLON"

#define LOG_FATAL(...) { \
                    char _LOG_buf[4096]; \
                    sprintf(_LOG_buf, __VA_ARGS__);\
                    logbase(_LOG_buf, LOG_COLOUR_FATAL, stderr);\
                 } "FORCE_SEMICOLON"


#endif //UNIGS_SERVER_LOGGER_
