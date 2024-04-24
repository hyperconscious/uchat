#include "home.h"

static void add_matching_chat(GObject *object) {
    Chat *chat = (Chat *)object;
    char *filter_text = get_entry_text(SEARCH_CHAT_ENTRY_ID);

    if (strcasestr(chat->name, filter_text) != NULL 
            && strcmp(chat->name, Client->name) != 0) {
        add_chat_sorted_to_visible_list_store(chat);
    //    guint added_chat_index = add_chat_sorted_to_visible_list_store(chat);
    //    if (chat->selected) {
    //        GtkListBoxRow *added_row = gtk_list_box_get_row_at_index(
    //                get_list_box(CHAT_LIST_BOX_ID),
    //                added_chat_index
    //        );
    //        set_chat_list_box_row_selected_style(added_row);
    //    }
    }
}

void filter_chats(void) {
    g_list_store_remove_all(visible_chats_list_store);
    list_store_for_each(all_chats_list_store, add_matching_chat);
}
