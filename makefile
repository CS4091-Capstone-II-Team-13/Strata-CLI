.PHONY: clean
.DEFAULT_GOAL := build

CC := "g++"
APP_NAME := "strata"
INCLUDE_PATH := "include"

build: src/*.cpp src/*/*.cpp
	$(CC) -I $(INCLUDE_PATH) $^ -o bins/linux/$(APP_NAME)
	$(CC) -Wall -I $(INCLUDE_PATH) $^ -o bins/windows/$(APP_NAME).exe

install: build
	@echo "Installing . . ."
	install -m 0755 bins/linux/$(APP_NAME) /usr/local/bin
	@echo "Complete ✓"

clean:
	rm -rf *.o $(APP_NAME)
	rm -f bins/linux/$(APP_NAME)
	rm -f bins/windows/$(APP_NAME).exe