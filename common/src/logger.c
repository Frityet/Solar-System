//
// Created by Frityet on 2021-12-20.
//

#include "logger.h"

#define LOG_COLOUR_CODE_INFO     "\x1b[39m"
#define LOG_COLOUR_CODE_DEBUG    "\x1b[90m"
#define LOG_COLOUR_CODE_WARNING  "\x1b[33m"
#define LOG_COLOUR_CODE_ERROR    "\x1b[31m"
#define LOG_COLOUR_CODE_FATAL    "\x1b[41m"

local char *filename;

void logbase(const char *msg, int line, const char *file, enum log_colour log_colour, FILE *stream)
{
    switch (log_colour) {
        default:
        case LOG_COLOUR_INFO:
            fprintf(stream, LOG_COLOUR_CODE_INFO "[%s:%d] %s\n", file, line, msg);
            break;
        case LOG_COLOUR_DEBUG:
            fprintf(stream, LOG_COLOUR_CODE_DEBUG "[%s:%d] %s\n", file, line, msg);
            break;
        case LOG_COLOUR_WARNING:
            fprintf(stream, LOG_COLOUR_CODE_WARNING "[%s:%d] %s\n", file, line, msg);
            break;
        case LOG_COLOUR_ERROR:
            fprintf(stream, LOG_COLOUR_CODE_ERROR "[%s:%d] %s\n", file, line, msg);
            break;
        case LOG_COLOUR_FATAL:
            fprintf(stream, LOG_COLOUR_CODE_FATAL "[%s:%d] %s\n", file, line, msg);
            break;
    }

    FILE *logfile = fopen(filename, "a");
    if (logfile != NULL) {
        fputs(msg, logfile);
    }
}

void initalise_logger(char *file)
{
    FILE *tmp = fopen(file, "w");
    if (tmp == NULL) {
        LOG_ERROR("Could not create logger file at %s!\n", file);
    }
    filename = file;
}

