#include "gui_util.h"

GtkWidget *get_widget(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_WIDGET(g_object);
}

GtkWindow *get_window(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_WINDOW(g_object);
}

GtkLabel *get_label(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_LABEL(g_object);
}

GtkEntry *get_entry(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_ENTRY(g_object);
}
