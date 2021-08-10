# -*- coding: utf8 -*-

FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR := $(shell dirname $(FILE_PATH))
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(FILE_PATH))))
BUILD_DIR := "$(PROJECT_DIR)/staging"
WITH_TEST := 1
TEST_FLAGS := \
	-D JustOnce_WithTest=${WITH_TEST} \
	-D ShaOne_WithTest=0 \
	-D Testly_WithTest=0

default: all

debug:
	@echo "FILE_PATH: $(FILE_PATH)"
	@echo "PROJECT_DIR: $(PROJECT_DIR)"
	@echo "PROJECT_NAME: $(PROJECT_NAME)"

clean:
	@rm -rf "$(BUILD_DIR)"

prepare:
	@mkdir -p "$(BUILD_DIR)"
	@(cd $(BUILD_DIR) && cmake ${TEST_FLAGS} ..)

build:
	@make -C "$(BUILD_DIR)"

run-test:
	@(([ ${WITH_TEST} = 1 ] && [ -f "$(BUILD_DIR)/JustOnceTest" ]) \
		&& "$(BUILD_DIR)/./JustOnceTest" ) || echo Skipping test ...

build-run: build run-test

all: prepare build-run