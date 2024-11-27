#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>


typedef enum FlsLogType {
    FlsDEBUG = 0,
    FlsINFO,
    FlsSUCCESS,
    FlsWARNING,
    FlsERROR,
} FlsLogType;

void fls_logger_level_set(FlsLogType log_level);
void fls_logger_file_set(FILE *file);
void fls_logger_file(FILE *file, FlsLogType log_type, const char *fmt, ...);
void fls_logger(FlsLogType log_type, const char *fmt, ...);


#endif // LOGGER_H
