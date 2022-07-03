#include <cstdlib>          //need std::free so it doesn't clash with Log::free()
#include "../common/stdio.h"
#include <string.h>
#include "log.h"

typedef struct {
    void (*callback)(LogType type, const char *text, void *user_data);
    void *callback_user_data;
} log_t;

static log_t logger;

void Log::init() {
    memset(&logger, 0, sizeof(logger));
}

void Log::free() {
}

void Log::set_callback(void (*callback)(LogType type, const char *text, void *user_data), void *user_data) {
    logger.callback = callback;
    logger.callback_user_data = user_data;
}

void Log::write_ap(LogType type, const char *fmt, va_list ap) {
    char *text;

    vasprintf(&text, fmt, ap);

    //TODO: we could be really fancy and queue these up on a thread
    printf("%s", text);

    if (logger.callback) {
        logger.callback(type, text, logger.callback_user_data);
    }

    std::free(text);
}

void Log::write(LogType type, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    Log::write_ap(type, fmt, ap);
    va_end(ap);
}

void Log::debug(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    Log::write_ap(LOG_TYPE_DEBUG, fmt, ap);
    va_end(ap);
}

void Log::info(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    Log::write_ap(LOG_TYPE_INFO, fmt, ap);
    va_end(ap);
}

void Log::warn(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    Log::write_ap(LOG_TYPE_WARN, fmt, ap);
    va_end(ap);
}

void Log::error(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    Log::write_ap(LOG_TYPE_ERROR, fmt, ap);
    va_end(ap);
}