#pragma once

#include <stdarg.h>

typedef enum {
    LOG_TYPE_DEBUG,
    LOG_TYPE_INFO,
    LOG_TYPE_WARN,
    LOG_TYPE_ERROR
} LogType;

namespace Log {
    void init();
    void free();

    void set_callback(void (*callaback)(LogType type, const char *text, void *user_data), void *user_data);

    void write_ap(LogType type, const char *fmt, va_list ap);
    void write(LogType type, const char *fmt, ...);
    void debug(const char *fmt, ...);
    void info(const char *fmt, ...);
    void warn(const char *fmt, ...);
    void error(const char *fmt, ...);
};