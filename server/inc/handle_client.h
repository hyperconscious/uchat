#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "string_utils.h"
#include "client_request_codes.h"
#include "packet.h"
#include "handle_registration.h"
#include "handle_login.h"
#include "handle_search_chat.h"

typedef struct {
    int client_socket;
} t_client_info;

void *handle_client(void *arg);

