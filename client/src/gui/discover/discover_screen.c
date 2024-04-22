#include "discover.h"

void on_discover_screen_show(void) {
    const int column_count = 4;
    const int row_count = 4;
    DiscoverPerson person = {.id = 0, .name = "Paul", .image_url = NULL};
    GtkGrid *discover_grid = GTK_GRID(get_widget(DISCOVER_GRID_ID));

    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < column_count; j++) {
            GtkWidget *discover_grid_item =
                    create_discover_grid_item(person.name, person.image_url);
            gtk_grid_attach(discover_grid, discover_grid_item, i, j, 1, 1);
        }
    }
}
