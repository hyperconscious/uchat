#include "home.h"

void delete_searched_chats(void) {
    int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));

    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
        if (chat && chat->searching && chat->messages == NULL)
            remove_chat(chat, all_chats_list_store);
    }

    /*   size = g_list_model_get_n_items(G_LIST_MODEL(visible_chats_list_store));

       for (int i = 0; i < size; i++) {
           Chat *chat = get_list_store_item_by_index(visible_chats_list_store, i);
           if (chat && chat->searching && chat->messages == NULL)
               remove_chat(chat, visible_chats_list_store);
       }*/
}
