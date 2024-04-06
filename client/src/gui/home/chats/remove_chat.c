#include "home.h"

void remove_chat(Chat *chat) {
    guint all_chats_list_store_index;
    g_list_store_find(all_chats_list_store, chat, &all_chats_list_store_index);

    guint visible_chats_list_store_index;
    g_list_store_find(visible_chats_list_store, chat,
                      &visible_chats_list_store_index);

    g_list_store_remove(all_chats_list_store, all_chats_list_store_index);
    g_list_store_remove(visible_chats_list_store,
                        visible_chats_list_store_index);
}
