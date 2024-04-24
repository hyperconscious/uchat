#include "home.h"

static gboolean check_is_chat_selected(gconstpointer a,
                                       gconstpointer b) {
    Chat *chat1 = (Chat *)a;
    Chat *chat2 = (Chat *)b;
    return chat1->selected == chat2->selected;
}
gboolean get_selected_chat_index(guint *index) {
    Chat *chat = create_chat(-1, NULL, NULL, NULL, 0, false, false, 0);
    chat->selected = true;
    return g_list_store_find_with_equal_func(
            all_chats_list_store,
            chat,
            check_is_chat_selected,
            index
    );
}
