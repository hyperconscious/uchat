CLIENT = uchat
SERVER = uchat_server
UTILS = libutils
SQLITE = libsqlite

CLIENT_DIR = client
SERVER_DIR = server
UTILS_DIR = utils
SQLITE_DIR = SQLite

all:
	@+make -sC $(SQLITE_DIR)
	@+make -sC $(UTILS_DIR)
	@+make -sC $(SERVER_DIR)
	@+make -sC $(CLIENT_DIR)

clean:
	@make -sC $(SQLITE_DIR) $@
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@

uninstall:
	@make -sC $(SQLITE_DIR) $@
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@
	
reinstall:
	@make -sC $(SQLITE_DIR) $@
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@

.PHONY: + all uninstall clean reinstall
    
