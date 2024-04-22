#include "home.h"

void create_searching_chat(t_db_chat *s_chat) {
    int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));
    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
        if (chat && ((strcmp(s_chat->name, chat->name) == 0)
                     || strcmp(s_chat->name, user_username) == 0)) {
            return;
        }
    }
    Chat *chat = create_chat(s_chat->owner_id, NULL, s_chat->name, NULL, 0, true,
                             get_current_time_millis());
    add_chat_sorted_to_all_list_store(chat);
}

