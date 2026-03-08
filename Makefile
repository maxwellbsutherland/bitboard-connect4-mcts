CC      := gcc
CFLAGS  := -Wall -Wextra -g -Iinclude

SRC_DIR := src
BIN_DIR := bin

TARGET := $(BIN_DIR)/c4.exe

SRCS := \
    $(wildcard $(SRC_DIR)/*.c) 

all: $(TARGET)

$(TARGET): $(SRCS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@echo Cleaning...
	@if exist $(TARGET) del $(TARGET)

.PHONY: all clean