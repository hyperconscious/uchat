CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11
SRC_DIR = src
OBJ_DIR = obj
API_DIR = SQLite
API_FILE = sqlite3

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

.PHONY: all uninstall clean reinstall

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -c $(API_DIR)/$(API_FILE).c -o $(OBJ_DIR)/$(API_FILE).o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

uninstall: clean

clean:
	@echo "Removing object files..."
	rm -f $(OBJ_FILES)
	@echo "Removing obj directory..."
	rm -rf $(OBJ_DIR)


reinstall: uninstall all
