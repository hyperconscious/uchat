#include "gui_util.h"

#define DISCOVER_GRID_ID "discover_grid"

typedef struct {
    long id;
    char *name;
    char *image_url;
} DiscoverPerson;

GtkWidget *create_discover_grid_item(char *name,
                                     char *image_url);
