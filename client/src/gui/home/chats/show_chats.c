#include "home.h"

void show_chats(t_list *chats) {
    all_chats_list_store = g_list_store_new(CHAT_TYPE);
    visible_chats_list_store = g_list_store_new(CHAT_TYPE);
    int chats_count = mx_list_size(chats);

    for (int i = 0; i < chats_count; i++) {
        Chat *chat = mx_get_element_by_index(chats, i);
        add_chat_sorted(chat);
    }

    gtk_list_box_bind_model(
            get_list_box(CHAT_LIST_BOX_ID),
            G_LIST_MODEL(visible_chats_list_store),
            create_chat_list_box_widget,
            NULL,
            NULL
    );
}
