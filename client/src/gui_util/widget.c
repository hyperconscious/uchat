#include "gui_util.h"

GtkWidget *get_widget(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_WIDGET(g_object);
}

bool get_widget_visible(char *id) {
    GtkWidget *widget = get_widget(id);
    return gtk_widget_get_visible(widget);
}

void show_widget(char *id) {
    GtkWidget *widget = get_widget(id);
    gtk_widget_show(widget);
}

void hide_widget(char *id) {
    GtkWidget *widget = get_widget(id);
    gtk_widget_hide(widget);
}
