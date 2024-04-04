#include "gui_util.h"

GtkWindow *get_window(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_WINDOW(g_object);
}

void open_window(char *id) {
    GtkWindow *window = get_window(id);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_present(window);
}

void close_window(char *id) {
    GtkWindow *window = get_window(id);
    gtk_window_close(window);
}
