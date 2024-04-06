#include "home.h"

static gboolean check_is_chat_selected(gconstpointer a,
                                gconstpointer b) {
    if (b == NULL) {}
    Chat *chat = (Chat *)a;
    return chat->selected;
}

gboolean get_selected_chat_index(guint *index) {
    return g_list_store_find_with_equal_func(
            all_chats_list_store,
            NULL,
            check_is_chat_selected,
            index
    );
}
