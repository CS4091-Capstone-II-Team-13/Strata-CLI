.PHONY: clean
.DEFAULT_GOAL := build

CC  := g++
WCC := x86_64-w64-mingw32-g++
APP_NAME := strata

# Include Paths
INCLUDE_PATH := src/include
LIB_PATH := libs


CFLAGS := -O3 -Wall -std=c++17

# httplib needs ssl, crypto, and pthread
LDFLAGS := -lssl -lcrypto -lz -lpthread -lsqlite3

INC_FLAGS := -I/usr/include -I$(INCLUDE_PATH) -I$(LIB_PATH)
STATIC_LIBRARIES := libs/strata-middleware-linux-amd64/libstrata.a

build: src/*.cpp src/*/*.cpp
	@mkdir -p bin/linux bin/windows
	@echo "Building Linux version..."
	$(CC) $(CFLAGS) $(INC_FLAGS) $^ $(STATIC_LIBRARIES) -o bin/linux/$(APP_NAME) $(LDFLAGS)

debug: src/*.cpp src/*/*.cpp
	@mkdir -p bin/debug
	$(CC) -g $(INC_FLAGS) $^ $(STATIC_LIBRARIES) -o bin/debug/$(APP_NAME) $(LDFLAGS)

install: build
	@echo "Installing . . ."
	install -m 0755 bin/linux/$(APP_NAME) /usr/local/bin
	@echo "Complete ✓"

clean:
	rm -rf *.o $(APP_NAME)
	rm -rf bin/