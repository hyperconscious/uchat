#include "gui_util.h"

static gboolean on_delete_event(void) {
    gtk_main_quit();
    return TRUE;
}

GtkWindow *get_window(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_WINDOW(g_object);
}

void open_window(char *id) {
    GtkWindow *window = get_window(id);
    g_signal_connect(window, "delete-event", G_CALLBACK(on_delete_event), NULL);
    gtk_window_present(window);
}

void close_window(char *id) {
    GtkWindow *window = get_window(id);
    gtk_widget_hide(GTK_WIDGET(window));
}
