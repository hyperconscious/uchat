#include "gui_util.h"

GtkWidget *get_widget(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_WIDGET(g_object);
}

void hide_widget(char *id) {
    GtkWidget *widget = get_widget(id);
    gtk_widget_hide(widget);
}
