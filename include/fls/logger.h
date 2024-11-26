#ifndef LOGGER_H
#define LOGGER_H


#include <stdio.h>

typedef enum flsLogType {
    flsDEBUG = 0,
    flsINFO,
    flsSUCCESS,
    flsWARNING,
    flsERROR,
} flsLogType;

void fls_logger_level_set(flsLogType log_level);
void fls_logger_file_set(FILE *file);
void fls_logger_file(FILE *file, flsLogType log_type, const char *fmt, ...);
void fls_loggger(flsLogType log_type, const char *fmt, ...);


#endif // LOGGER_H
