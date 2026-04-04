.PHONY: clean
.DEFAULT_GOAL := build

CC := g++
APP_NAME := strata
# local project includes
INCLUDE_PATH := include

# Node++ specific paths (tells the linker how to include <nodepp/nodepp.h>)
NODEPP_PATH := libs/Nodepp/include
NODEPP_LIB  := libs/Nodepp/lib

# Compilation Flags: 
CFLAGS := -O3 -Wall
LDFLAGS := -lssl -lcrypto -lz -lpthread

build: src/*.cpp src/*/*.cpp
	@mkdir -p bins/linux bins/windows
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -I $(NODEPP_PATH) $^ -o bins/linux/$(APP_NAME) $(LDFLAGS)
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -I $(NODEPP_PATH) $^ -o bins/windows/$(APP_NAME).exe $(LDFLAGS)

debug: src/*.cpp src/*/*.cpp
	@mkdir -p bins/debug
	$(CC) -g -I $(INCLUDE_PATH) -I $(NODEPP_PATH) $^ -o bins/debug/$(APP_NAME) $(LDFLAGS)

install: build
	@echo "Installing . . ."
	install -m 0755 bins/linux/$(APP_NAME) /usr/local/bin
	@echo "Complete ✓"

clean:
	rm -rf *.o $(APP_NAME)
	rm -rf bins/