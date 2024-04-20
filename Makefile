CLIENT = uchat
SERVER = uchat_server
UTILS = libutils
SQLITE = libsqlite
SOUP = libsoap

CLIENT_DIR = client
SERVER_DIR = server
UTILS_DIR = utils
SQLITE_DIR = SQLite
SOUP_DIR = libs/libsoup/libsoup

all:
	 #@make -sC $(SOUP_DIR)
	@make -sC $(SQLITE_DIR)
	@make -sC $(UTILS_DIR)
	@make -sC $(CLIENT_DIR)
	@make -sC $(SERVER_DIR)

clean:
	 #@make -sC $(SOUP_DIR)
	@make -sC $(SQLITE_DIR) $@
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@

uninstall:
	 #@make -sC $(SOUP_DIR)
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@
	@make -sC $(SQLITE_DIR) $@
	
reinstall:
	 #@make -sC $(SOUP_DIR)
	@make -sC $(SQLITE_DIR) $@
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@

.PHONY: + all uninstall clean reinstall
    
