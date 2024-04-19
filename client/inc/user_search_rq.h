#pragma once

#include "socket_operations.h"
#include "packet.h"
#include "client_requests.h"

char** search_chats(char* searching_chat, uint16_t *count, char* server_address, int port);

