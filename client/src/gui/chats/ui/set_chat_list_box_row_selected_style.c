#include "home.h"

static void remove_selected_class(GtkListBoxRow *row) {
    GtkBox *root_box = get_box_from_container(GTK_CONTAINER(row), 0);
    gtk_widget_set_name(GTK_WIDGET(root_box), NULL);
}

void set_chat_list_box_row_selected_style(GtkListBoxRow *selected_row) {
    GtkListBox *chat_list = get_list_box(PERSONAL_CHAT_LIST_BOX_ID);
    GtkBox *root_box = get_box_from_container(GTK_CONTAINER(selected_row), 0);
    list_box_for_each(chat_list, remove_selected_class);
    gtk_widget_set_name(GTK_WIDGET(root_box), "selected_chat_list_item");
}
