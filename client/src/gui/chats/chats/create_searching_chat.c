#include "home.h"

void create_searching_chat(char* name) {
    int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));
    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
        if (chat && (strcmp(chat->name, name) == 0)) {
            return;
        }
    }
    Chat* chat = create_chat(0, NULL, name, NULL, 0, true, 
                                get_current_time_millis());
    add_chat_sorted_to_all_list_store(chat);
}

