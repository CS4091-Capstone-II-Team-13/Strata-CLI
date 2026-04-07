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
LDFLAGS := -lssl -lcrypto -lz -lpthread

build: src/*.cpp src/*/*.cpp
	@mkdir -p bins/linux bins/windows
	
	@echo "Building Linux version..."
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -I $(LIB_PATH) $^ -o bins/linux/$(APP_NAME) $(LDFLAGS)
	
	@echo "Building Windows version..."
	@if command -v $(WCC) > /dev/null; then \
		$(WCC) $(CFLAGS) -I $(INCLUDE_PATH) -I $(LIB_PATH) $^ -o bins/windows/$(APP_NAME).exe $(LDFLAGS); \
		echo "Windows build complete ✓"; \
	else \
		echo "----------------------------------------------------------"; \
		echo "WARNING: Windows cross-compiler ($(WCC)) not found."; \
		echo "To build for Windows on Debian/Ubuntu, run:"; \
		echo "  sudo apt install g++-mingw-w64-x86-64"; \
		echo "Skipping Windows build..."; \
		echo "----------------------------------------------------------"; \
	fi

debug: src/*.cpp src/*/*.cpp
	@mkdir -p bins/debug
	$(CC) -g -I $(INCLUDE_PATH) -I $(LIB_PATH) $^ -o bins/debug/$(APP_NAME) $(LDFLAGS)

install: build
	@echo "Installing . . ."
	install -m 0755 bins/linux/$(APP_NAME) /usr/local/bin
	@echo "Complete ✓"

clean:
	rm -rf *.o $(APP_NAME)
	rm -rf bins/