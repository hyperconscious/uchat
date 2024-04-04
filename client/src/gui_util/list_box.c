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

int count_list_box_items(GtkListBox *list_box) {
    gint count = 0;

    while (gtk_list_box_get_row_at_index(list_box, count) != NULL)
        count++;

    return (int)count;
}

GtkListBoxRow *list_box_append(char *id,
                               GtkWidget *widget) {
    GtkListBox *list_box = get_list_box(id);

    gtk_list_box_insert(list_box, widget, -1);
    int new_item_index = count_list_box_items(list_box) - 1;

    return gtk_list_box_get_row_at_index(list_box, new_item_index);
}

