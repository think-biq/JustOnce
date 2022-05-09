# -*- coding: utf8 -*-

FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR := $(shell dirname $(FILE_PATH))
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(FILE_PATH))))
BUILD_DIR ?= $(PROJECT_DIR)/staging
BUILD_MODE ?= Release # Either Debug or Release
BUILD_SHARED_LIBS ?= OFF
GRIND ?= valgrind
GRIND_OPTS ?= --show-leak-kinds=all --leak-check=full --track-origins=yes -v
WITH_TEST ?= 1
TEST_FLAGS := -D JustOnce_WithTest=${WITH_TEST} \
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
	@cmake -B $(BUILD_DIR) -D CMAKE_BUILD_TYPE=${BUILD_MODE} \
		-D BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} ${TEST_FLAGS} \
		-D JustOnce_WithTest=1 \
		-D BCRYPT=1 \
		-S $(PROJECT_DIR)

build:
	@cmake --build $(BUILD_DIR)

run-test:
	@(([ ${WITH_TEST} = 1 ] && [ -f "$(BUILD_DIR)/JustOnceTest" ]) \
		&& "$(BUILD_DIR)/./JustOnceTest" ) || echo Skipping test ...

docs: clean-docs icon
	doxygen docs/doxygen.cfg > docs/doxygen.log 2> docs/doxygen.err.log

open-docs:
	open docs/html/index.html

clean-docs:
	rm -rf docs/{html,latex}
	rm -f docs/doxygen*.log

build-run: build run-test

all: prepare build-run

icon: prepare
	convert -background white -fill black \
	  -size 128x64 -gravity center label:".:* JustOnce *:." "$(PROJECT_DIR)/docs/icon.png"

grind:
	mkdir -p log
	$(GRIND) $(GRIND_OPTS) "$(BUILD_DIR)/./JustOnceTest" > log/debug 2> log/error