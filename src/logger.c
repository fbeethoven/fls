#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#include "fls/logger.h"


static char *ANSI_ESCAPE = "\033[";

static flsLogType fls_log_level;
static FILE *fls_file;


void fls_logger_level_set(flsLogType log_level) {
    fls_log_level = log_level;
}

void fls_logger_file_set(FILE *file) {
    fls_file = file;
}

void fls_logger_file(FILE *file, flsLogType log_type, const char *fmt, ...) {
    if (file == NULL) {
        fls_logger_file(stderr, flsERROR, "file not defined");
        fflush(file);
        return;
    }

    va_list args;
    va_start(args, fmt);

    char buf_fmt[1024];

    switch(log_type) {
        case flsDEBUG:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;47;30m[DEBUG]\033[0m %s\n", fmt);
            vfprintf(file, buf_fmt, args);
            break;
        case flsINFO:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;44;37m[INFO]\033[0m \033[34m%s\033[0m\n", fmt);
            vfprintf(file, buf_fmt, args);
            break;
        case flsSUCCESS:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;42;37m[SUCCESS]\033[0m \033[32m%s\033[0m\n", fmt);
            vfprintf(file, buf_fmt, args);
            break;
        case flsWARNING:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;43;31m[WARNING]\033[0m \033[33m%s\033[0m\n", fmt);
            vfprintf(file, buf_fmt, args);
            break;
        case flsERROR:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;41;37m[ERROR]\033[0m \033[31m%s\033[0m\n", fmt);
            vfprintf(file, buf_fmt, args);
            break;
        default:
            fls_logger_file(stderr, flsERROR, "UNREACHABLE");
            break;
    }

    va_end(args);
    fflush(file);
}

static void v_log_to_file_or_default_f(FILE *file, const char * fmt, va_list args) {
    if (fls_file != NULL) {
        vfprintf(fls_file, fmt, args);
        fflush(fls_file);
        return;
    }
    vfprintf(file, fmt, args);
    fflush(file);
}

void fls_loggger(flsLogType log_type, const char *fmt, ...) {
    if (log_type < fls_log_level) {
        return;
    }

    va_list args;
    va_start(args, fmt);

    char buf_fmt[1024];

    switch(log_type) {
        case flsDEBUG:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;47;30m[DEBUG]\033[0m %s\n", fmt);
            v_log_to_file_or_default_f(stdout, buf_fmt, args);
            break;
        case flsINFO:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;44;37m[INFO]\033[0m \033[34m%s\033[0m\n", fmt);
            v_log_to_file_or_default_f(stdout, buf_fmt, args);
            break;
        case flsSUCCESS:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;42;37m[SUCCESS]\033[0m \033[32m%s\033[0m\n", fmt);
            v_log_to_file_or_default_f(stdout, buf_fmt, args);
            break;
        case flsWARNING:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;43;31m[WARNING]\033[0m \033[33m%s\033[0m\n", fmt);
            v_log_to_file_or_default_f(stdout, buf_fmt, args);
            break;
        case flsERROR:
            snprintf(buf_fmt, sizeof(buf_fmt), "\033[1;41;37m[ERROR]\033[0m \033[31m%s\033[0m\n", fmt);
            v_log_to_file_or_default_f(stderr, buf_fmt, args);
            break;
        default:
            fls_logger_file(stderr, flsERROR, "UNREACHABLE");
            break;
    }

    va_end(args);
}

