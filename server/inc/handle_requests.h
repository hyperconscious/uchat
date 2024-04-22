#pragma once

#include "packet.h"
#include <stdio.h>
#include "client_status_code.h"
#include "database.h"

void handle_login(int client_socket);
void handle_sign_up(int client_socket);

void handle_search_chat(int client_socket);
void handle_add_chat(int client_socket);
void handle_get_chats(int client_socket);
void handle_add_user_to_chat(int client_socket);
void handle_discover(int client_socket);
