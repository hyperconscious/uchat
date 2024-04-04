#include "home.h"

void remove_selected_class(GtkListBoxRow *row) {
    update_class(
            GTK_WIDGET(row),
            "chat_list_item_selected",
            "unread_chat_list_item"
    );
}

void set_selected_chat_style(void) {
    GtkListBox *chat_list = get_list_box(CHAT_LIST_ID);
    GtkListBoxRow *selected_row = gtk_list_box_get_selected_row(chat_list);

    list_box_for_each(chat_list, remove_selected_class);
    update_class(
            GTK_WIDGET(selected_row),
            "unread_chat_list_item",
            "chat_list_item_selected"
    );
}
