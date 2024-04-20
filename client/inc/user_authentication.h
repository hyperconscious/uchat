#pragma once

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <string.h>
#include "packet.h"
#include "socket_operations.h"
#include "client_requests.h"
#include "client_status_code.h"

#define AUTH_WINDOW_ID "auth_window"
#define HOME_WINDOW_ID "home_window"
#define SUCCESSFUL "success"

char* process_user_authentication(char* server_address, int port,
                                                 char* username, char* password,
                                                 t_client_rq authentication_code);

