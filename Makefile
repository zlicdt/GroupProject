# Makefile
# For makefile to work, gcc must be installed on the system
# "pacman -S gcc"

CC := $(shell command -v gcc 2>/dev/null)
ifeq ($(CC),)
$(error "gcc is not installed on this system")
endif

SOURCES := main.c io.c time.c verify.c menu.c clear.c

CFLAGS := -g -lm

OBJECT := main

CACHE_FILE := bookinfo/*

all: project

project:
	@echo "[CC] Sources"
	@gcc ${CFLAGS} ${SOURCES} -o main

clean:
	@echo "[CLEAN] ${OBJECT}"
	@rm -rf ${OBJECT}
	@echo "[CLEAN] ${CACHE_FILE}"
	@rm -rf ${CACHE_FILE}
help:
	@echo "Usage:"
	@echo "  make project       - Build this project"
	@echo "  make clean	    - Clean workspace"
