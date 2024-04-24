#pragma once

#include "packet.h"
#include <stdio.h>
#include "client_status_code.h"
#include "database.h"

void handle_connection(int client_socket);

void handle_login(int client_socket, sqlite3 *db);
void handle_sign_up(int client_socket, sqlite3 *db);

void handle_search_chat(int client_socket, sqlite3 *db);
void handle_add_chat(int client_socket, sqlite3 *db);
void handle_get_chats(int client_socket, sqlite3 *db);
void handle_add_user_to_chat(int client_socket, sqlite3 *db);
void handle_remove_chat(int client_socket, sqlite3 *db);

void handle_discover(int client_socket, sqlite3 *db);
void handle_get_login_by_id(int client_socket, sqlite3 *db);
void handle_change_username(int client_socket, sqlite3 *db);

void handle_remove_message(int client_socket, sqlite3 *db);
void handle_add_message(int client_socket, sqlite3 *db);
void handle_get_messages(int client_socket, sqlite3 *db);
void handle_delete_message(int client_socket, sqlite3 *db);
