.PHONY: clean
.DEFAULT_GOAL := build

CC := "g++"
APP_NAME := "strata"

build:
	$(CC) src/main.cpp -o bins/$(APP_NAME).out

install: build
	@echo "Installing . . ."
	install -m 0755 $(APP_NAME) /usr/local/bin
	@echo "Complete ✓"

clean:
	rm -rf *.o $(APP_NAME)