#include "logger.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    log_config_t cfg = {
        .file_path = "build/test.log",
        .max_file_size = 1024,
        .max_backups = 2,
        .to_console = 1,
        .level = LOG_LEVEL_DEBUG,
        .use_utc = 0
    };
    if (log_init(&cfg) != 0) {
        fprintf(stderr, "init failed\n");
        return 1;
    }
    for (int i = 0; i < 200; ++i) {
        LOG_DEBUG("test", "message %d", i);
        LOG_INFO("test", "info %d", i);
        LOG_WARN("test", "warn %d", i);
        LOG_ERROR("test", "error %d", i);
    }
    log_close();
    return 0;
}