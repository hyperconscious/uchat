#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "string_utils.h"

typedef struct {
    int client_socket;
    char login[50];
} t_client_info;

void *handle_client(void *arg);

