#include "gui_util.h"

GtkBox *get_box(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_BOX(g_object);
}

void add_widget_to_box(GtkBox *box,
                       GtkWidget *widget,
                       bool expand,
                       bool fill,
                       int padding) {
    gtk_box_pack_start(box, widget, expand, fill, padding);
    gtk_widget_show(widget);
}
