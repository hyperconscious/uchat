#include "home.h"

void show_chats_am_in(){
    int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));

    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
        if (chat && !chat->searching) {
            add_chat_sorted_to_visible_list_store(chat);
        }
    }
    
}

