#include "gui_util.h"

GtkListBox *get_list_box(char *id) {
    GtkWidget *list_box = get_widget(id);
    return GTK_LIST_BOX(list_box);
}

void list_box_for_each(GtkListBox *list_box,
                       void (*ptr)(GtkListBoxRow *row)) {
    gint index = 0;
    while (gtk_list_box_get_row_at_index(list_box, index) != NULL) {
        GtkListBoxRow *row = gtk_list_box_get_row_at_index(list_box, index);
        ptr(row);
        index++;
    }
}

int get_list_box_selected_item_index(char *id) {
    GtkListBox *list_box = get_list_box(id);
    GtkListBoxRow *selected_row = gtk_list_box_get_selected_row(list_box);
    return gtk_list_box_row_get_index(selected_row);
}

int get_list_box_item_count(GtkListBox *list_box) {
    gint count = 0;

    while (gtk_list_box_get_row_at_index(list_box, count) != NULL)
        count++;

    return (int)count;
}

GtkListBoxRow *list_box_append(char *id,
                               GtkWidget *widget) {
    GtkListBox *list_box = get_list_box(id);

    gtk_list_box_insert(list_box, widget, -1);
    int new_item_index = get_list_box_item_count(list_box) - 1;

    return gtk_list_box_get_row_at_index(list_box, new_item_index);
}

void clear_list_box(char *id) {
    GtkContainer *list_box = GTK_CONTAINER(get_list_box(id));
    GList *children, *iter;

    children = gtk_container_get_children(list_box);
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}
