#pragma once

#include "string_utils.h"
#include "socket_operations.h"
#include "threads.h"
#include "handle_client.h"
#include "database.h"

#define MAX_CLIENTS 128

void daemon();
