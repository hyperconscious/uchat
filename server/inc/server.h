#pragma once

#include "string_utils.h"
#include "socket_operations.h"
#include "threads.h"
#include "handle_client.h"
//#include <sys/sysinfo.h>
#include "database.h"

#define MAX_CLIENTS 128// (get_nprocs_conf() * 128)

