#include "home.h"

Chat *get_selected_chat(void) {
    guint selected_chat_index;
    get_selected_chat_index(&selected_chat_index);
    return get_list_store_item_by_index(all_chats_list_store,
                                        selected_chat_index);
}
