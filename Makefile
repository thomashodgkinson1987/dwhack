#**************************************************************************************************
#
#   raylib makefile for Desktop platforms, Raspberry Pi, Android and HTML5
#
#   Copyright (c) 2013-2019 Ramon Santamaria (@raysan5)
#
#   This software is provided "as-is", without any express or implied warranty. In no event
#   will the authors be held liable for any damages arising from the use of this software.
#
#   Permission is granted to anyone to use this software for any purpose, including commercial
#   applications, and to alter it and redistribute it freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not claim that you
#     wrote the original software. If you use this software in a product, an acknowledgment
#     in the product documentation would be appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be misrepresented
#     as being the original software.
#
#     3. This notice may not be removed or altered from any source distribution.
#
#**************************************************************************************************

.PHONY: all clean

CC = gcc

PROJECT_NAME   ?= dwhack
BUILD_MODE     ?= DEBUG

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
RES_DIR = res
LIB_DIR = lib

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

CFLAGS += -std=c11 -Wall -Wno-missing-braces -Wextra -Wmissing-prototypes -D_DEFAULT_SOURCE
INCLUDE_PATHS = -I./include/
LDFLAGS += -Wl,-rpath,./lib/
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lc

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRC_FILES = $(call rwildcard, $(SRC_DIR), *.c)
OBJS = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all:
	make $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CC) -v -o ./$(BIN_DIR)/$(PROJECT_NAME) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)
	ln -sf ./../$(RES_DIR) ./$(BIN_DIR)/
	ln -sf ./../$(LIB_DIR) ./$(BIN_DIR)/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -v -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS)

clean:
	rm -f ./$(OBJ_DIR)/*.o
	rm -f ./$(BIN_DIR)/$(PROJECT_NAME)
	rm -f ./$(BIN_DIR)/$(RES_DIR)
	rm -f ./$(BIN_DIR)/$(LIB_DIR)
	@echo Cleaning done
