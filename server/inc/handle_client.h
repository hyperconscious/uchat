#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "string_utils.h"
#include "client_codes.h"

typedef struct {
    int client_socket;
} t_client_info;

void *handle_client(void *arg);

