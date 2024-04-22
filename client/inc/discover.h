#pragma once

#include "home.h"
#include "gui_util.h"

#define DISCOVER_GRID_ID "discover_grid"

GtkWidget *create_discover_grid_item(char *name,
                                     char *image_url);
