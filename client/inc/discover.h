#pragma once

#include "home.h"
#include "gui_util.h"

#define DISCOVER_GRID_ID "discover_grid"

extern int Port;
extern char *serverAddress;
extern Person *Client;

GtkWidget *create_discover_grid_item(Person discovered_chat);
