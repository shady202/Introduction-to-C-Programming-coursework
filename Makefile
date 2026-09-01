CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99
TARGET_UNIX := bin/assignment
TARGET_WIN := bin/assignment.exe
SRC := src/main.c

ifeq ($(OS),Windows_NT)
TARGET := $(TARGET_WIN)
else
TARGET := $(TARGET_UNIX)
endif

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $(SRC)

run: $(TARGET)
ifeq ($(OS),Windows_NT)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
	rm -f $(TARGET_UNIX) $(TARGET_WIN) *.o *.obj

.PHONY: all run clean
