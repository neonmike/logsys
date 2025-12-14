CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -O2
BUILD_DIR := build
LIB := $(BUILD_DIR)/liblogsys.a
OBJ := $(BUILD_DIR)/logger.o

.PHONY: all clean test lib

all: lib

lib: $(LIB)

$(OBJ): src/logger.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

tests/test_logger: tests/test_logger.c $(LIB)
	$(CC) $(CFLAGS) $< $(LIB) -o $@

test: lib tests/test_logger
	./tests/test_logger

clean:
	rm -rf $(BUILD_DIR) tests/test_logger