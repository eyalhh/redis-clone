# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -O2 -I./src -I./pkg/hashmap -I./pkg/networking -I./pkg/aof

# Directories
SRC_DIR := src
PKG_DIR := pkg
CLIENT_DIR := client
BIN_DIR := bin
BUILD_DIR := build

# Targets
SERVER_BIN := $(BIN_DIR)/redis-clone
CLIENT_BIN := $(BIN_DIR)/demo-client

# Source files
SERVER_SRCS := $(SRC_DIR)/main.c \
               $(PKG_DIR)/hashmap/hashmap.c \
               $(PKG_DIR)/networking/networking.c \
               $(PKG_DIR)/aof/aof.c

CLIENT_SRCS := $(CLIENT_DIR)/democlient.c

# Object files (map sources to build directory)
SERVER_OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SERVER_SRCS))
CLIENT_OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(CLIENT_SRCS))

# Default target
all: $(SERVER_BIN) $(CLIENT_BIN)

# Build server binary
$(SERVER_BIN): $(SERVER_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Build client binary
$(CLIENT_BIN): $(CLIENT_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile rule: put .o files in build/ mirroring directory structure
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(SERVER_BIN) $(CLIENT_BIN)

.PHONY: all clean
