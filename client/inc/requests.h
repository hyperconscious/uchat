#pragma once

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <string.h>
#include "socket_operations.h"
#include "client_request_codes.h"
#include "client_status_code.h"
#include "packet.h"
#include "types.h"
#include "discover.h"

#define AUTH_WINDOW_ID "auth_window"
#define HOME_WINDOW_ID "home_window"
#define SUCCESSFUL "success"



char* rq_process_user_authentication(char* server_address, int port,
                                        char* username, char* password,
                                        t_client_rq authentication_code,
                                        uint32_t *id, uint16_t language);

t_db_chat* rq_search_chats(char* searching_chat, uint16_t *count,
                           char* server_address, int port);
uint32_t rq_create_chat(char* name, uint32_t owner_id,
                        bool is_private,
                        char* server_address, int port);
t_db_chat* rq_get_chats(uint32_t owner_id, uint16_t *count, char* server_address, int port);
void rq_add_user_to_chat(uint32_t user_id, uint32_t chat_id, char*
                         server_address, int port);

Person* rq_discover(uint32_t id, uint16_t *count, char* server_address, int port);

char* rq_get_login_by_id(uint32_t id, char* server_address, int port);
void change_username_rq(uint32_t id, char* new_username, char* server_address, int port);

int rq_add_message(uint32_t user_id, uint32_t chat_id, char* text, 
                    char* server_address, int port);

uint32_t rq_edit_message(uint32_t msg_id, char* text, 
                    char* server_address, int port);

uint32_t rq_remove_message(uint32_t msg_id, char* server_address, int port);

t_list* rq_get_messages_from_chat(uint32_t chat_id, char* search_text,
                                 char* server_address, int port);

uint32_t rq_edit_msg(uint32_t msg_id, char* msg_text, char* server_address, int port);

void rq_delete_message(uint32_t id, char* server_address, int port);

uint32_t rq_remove_chat(uint32_t chat_id, char* server_address, int port);


