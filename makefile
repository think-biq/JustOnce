# -*- coding: utf8 -*-

FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR := $(shell dirname $(FILE_PATH))
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(FILE_PATH))))
BUILD_DIR := "$(PROJECT_DIR)/cmake"

.default: debug

debug:
	@echo "FILE_PATH: $(FILE_PATH)"
	@echo "PROJECT_DIR: $(PROJECT_DIR)"
	@echo "PROJECT_NAME: $(PROJECT_NAME)"

clean:
	rm -rf "$(BUILD_DIR)"

prepare:
	mkdir -p "$(BUILD_DIR)"
	(cd $(BUILD_DIR) && cmake ..)

build:
	make -C "$(BUILD_DIR)"

run:
	$(BUILD_DIR)/./JustOnce