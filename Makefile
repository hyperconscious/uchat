CLIENT = uchat
SERVER = uchat_server
UTILS = libutils

CLIENT_DIR = client
SERVER_DIR = server
UTILS_DIR = utils

all:
	@make -sC $(UTILS_DIR)
	@make -sC $(SERVER_DIR)
	@make -sC $(CLIENT_DIR)

clean:
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@

uninstall:
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@
	
reinstall:
	@make -sC $(UTILS_DIR) $@
	@make -sC $(SERVER_DIR) $@
	@make -sC $(CLIENT_DIR) $@

.PHONY: + all uninstall clean reinstall
    
