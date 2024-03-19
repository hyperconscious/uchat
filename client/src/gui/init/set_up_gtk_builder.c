#include "init.h"

void set_up_gtk_builder(void) {
    GError *err = NULL;
    GtkBuilder *builder = gtk_builder_new();
    bool is_builder_successfully_added =
            gtk_builder_add_from_file(builder, GLADE_FILE_PATH, &err);

    if (!is_builder_successfully_added) {
        g_critical("Add GtkBuilder error: %s", err->message);
        g_error_free(err);
        exit(EXIT_FAILURE);
    }

    gtk_builder_connect_signals(builder, NULL);
    Builder = builder;
}
