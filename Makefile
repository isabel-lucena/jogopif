CC          = gcc
CFLAGS      = -Wall -Werror -g -I$(INCLUDE_DIR) -Iraylib/include
PROJ_NAME   = escapif
BUILD_DIR   = build
OBJ_DIR     = $(BUILD_DIR)/obj
SRC_DIR     = src
INCLUDE_DIR = include

# raylib: vem junto no repositório (pasta raylib/), versão Linux/WSL.
# Cada pessoa só precisa de: sudo apt install build-essential libgl1-mesa-dev libx11-dev
# No macOS: brew install raylib e troquem as linhas abaixo por:
# CFLAGS += -I/opt/homebrew/include
# LDFLAGS = -L/opt/homebrew/lib
# LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
LIBS = -Lraylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_FILES = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(OBJ_FILES)
	@echo Criando $(BUILD_DIR)/$(PROJ_NAME)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(PROJ_NAME) $(OBJ_FILES) $(LDFLAGS) $(LIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR): $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(wildcard $(INCLUDE_DIR)/*.h)
	@echo Compilando $@...
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(BUILD_DIR)/$(PROJ_NAME)

.PHONY: all clean run
