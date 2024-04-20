#include "home.h"

void remove_chat(Chat *chat, GListStore *list) {
    guint chat_index;
    g_list_store_find(list, chat, &chat_index);
    g_list_store_remove(list, chat_index);
}
