# -*- coding: utf8 -*-

FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR := $(shell dirname $(FILE_PATH))
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(FILE_PATH))))
BUILD_DIR := "$(PROJECT_DIR)/staging"
BUILD_TEST_FLAG := -D JustOnce_WithTest=0

default: all

debug:
	@echo "FILE_PATH: $(FILE_PATH)"
	@echo "PROJECT_DIR: $(PROJECT_DIR)"
	@echo "PROJECT_NAME: $(PROJECT_NAME)"

clean:
	@rm -rf "$(BUILD_DIR)"

prepare:
	@mkdir -p "$(BUILD_DIR)"
	@(cd $(BUILD_DIR) && cmake ${BUILD_TEST_FLAG} ..)

build:
	@make -C "$(BUILD_DIR)"

run-test:
	@(test -f "$(BUILD_DIR)/JustOnceTes" && "$(BUILD_DIR)/./JustOnceTes" ) || echo Skipping test ...

build-run: build run-test

all: prepare build-run