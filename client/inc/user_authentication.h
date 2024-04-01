#pragma once

#include "packet.h"
#include "socket_operations.h"
#include "handle_client_codes.h"
#include "client_status_code.h"

t_client_status_code process_user_authentication(char* server_address, int port,
                                                 char* username, char* password,
                                                 t_client_codes authentication_code);

