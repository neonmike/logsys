#ifndef LOGSYS_LOGGER_H
#define LOGSYS_LOGGER_H

#include <stddef.h>

typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_NONE = 4
} log_level_t;

typedef struct {
    const char *file_path;
    size_t max_file_size;
    int max_backups;
    int to_console;
    log_level_t level;
    int use_utc;
} log_config_t;

int log_init(const log_config_t *config);
void log_set_level(log_level_t level);
void log_close(void);
void log_log(log_level_t level, const char *module, const char *fmt, ...);

#define LOG_DEBUG(module, fmt, ...) log_log(LOG_LEVEL_DEBUG, module, fmt, ##__VA_ARGS__)
#define LOG_INFO(module, fmt, ...)  log_log(LOG_LEVEL_INFO,  module, fmt, ##__VA_ARGS__)
#define LOG_WARN(module, fmt, ...)  log_log(LOG_LEVEL_WARN,  module, fmt, ##__VA_ARGS__)
#define LOG_ERROR(module, fmt, ...) log_log(LOG_LEVEL_ERROR, module, fmt, ##__VA_ARGS__)

#endif