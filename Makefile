# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -g -D_ISOC99_SOURCE

# Source directory
SRC_DIR = src

# Object directory
OBJ_DIR = obj

# Binary directory
BIN_DIR = bin

# Name of the executable
TARGET = $(BIN_DIR)/program

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Header files
DEPS = $(wildcard $(SRC_DIR)/*.h)

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean

# Include dependencies
-include $(DEPS:.h=.d)