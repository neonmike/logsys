#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

static log_config_t g_cfg;
static FILE *g_fp = NULL;
static int g_initialized = 0;

static int rotate_logs(const char *path, int max_backups) {
    if (max_backups <= 0) return 0;
    char old_name[4096];
    char new_name[4096];
    for (int i = max_backups - 1; i >= 0; --i) {
        if (i == 0) {
            snprintf(old_name, sizeof(old_name), "%s", path);
        } else {
            snprintf(old_name, sizeof(old_name), "%s.%d", path, i);
        }
        snprintf(new_name, sizeof(new_name), "%s.%d", path, i + 1);
        if (access(old_name, F_OK) == 0) {
            rename(old_name, new_name);
        }
    }
    return 0;
}

static void ensure_rotation() {
    if (!g_fp || g_cfg.max_file_size == 0) return;
    long pos = ftell(g_fp);
    if (pos < 0) return;
    if ((size_t)pos >= g_cfg.max_file_size) {
        fflush(g_fp);
        fclose(g_fp);
        g_fp = NULL;
        rotate_logs(g_cfg.file_path, g_cfg.max_backups);
        g_fp = fopen(g_cfg.file_path, "a");
    }
}

static const char* level_str(log_level_t lvl) {
    switch (lvl) {
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_WARN:  return "WARN";
        case LOG_LEVEL_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

int log_init(const log_config_t *config) {
    if (!config) return -1;
    g_cfg = *config;
    g_fp = NULL;
    g_initialized = 1;
    if (g_cfg.file_path && g_cfg.file_path[0]) {
        g_fp = fopen(g_cfg.file_path, "a");
        if (!g_fp) return -2;
    }
    return 0;
}

void log_set_level(log_level_t level) {
    g_cfg.level = level;
}

void log_close(void) {
    if (g_fp) {
        fflush(g_fp);
        fclose(g_fp);
        g_fp = NULL;
    }
    g_initialized = 0;
}

static void format_time(char *buf, size_t len) {
    time_t t = time(NULL);
    struct tm tm_s;
    if (g_cfg.use_utc) {
        gmtime_r(&t, &tm_s);
    } else {
        localtime_r(&t, &tm_s);
    }
    strftime(buf, len, "%Y-%m-%d %H:%M:%S", &tm_s);
}

void log_log(log_level_t level, const char *module, const char *fmt, ...) {
    if (!g_initialized) return;
    if (level < g_cfg.level) return;

    char ts[64];
    format_time(ts, sizeof(ts));

    char msg[4096];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    if (g_cfg.to_console) {
        fprintf((level >= LOG_LEVEL_ERROR) ? stderr : stdout,
                "%s [%s] %s: %s\n", ts, level_str(level), module ? module : "-", msg);
    }

    if (g_fp) {
        fprintf(g_fp, "%s [%s] %s: %s\n", ts, level_str(level), module ? module : "-", msg);
        fflush(g_fp);
        ensure_rotation();
    }
}