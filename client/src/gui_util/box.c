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

void remove_first_child_from_box(GtkBox *box) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(box));
    if (children != NULL) {
        GtkWidget *first_child = GTK_WIDGET(children->data);
        gtk_container_remove(GTK_CONTAINER(box), first_child);
        g_list_free(children);
    }
}

guint get_box_child_count(GtkBox *box) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(box));
    if (children != NULL) {
        guint child_count = g_list_length(children);
        g_list_free(children);
        return child_count;
    }
    else {
        return 0;
    }
}
