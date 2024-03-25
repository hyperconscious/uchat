#include "gui_util.h"

void open_window(char *id) {
    GtkWindow *window = get_window(id);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_present(window);
}

void close_window(char *id) {
    GtkWindow *window = get_window(id);
    gtk_window_close(window);
}
