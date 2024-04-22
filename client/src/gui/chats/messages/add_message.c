#include "home.h"

void add_message(int chat_index,
                 Message *message) {
    Chat *chat = get_list_store_item_by_index(all_chats_list_store,
                                              chat_index);
    if (chat->messages == NULL) {
        t_list *messages = mx_create_node(message);
        chat->messages = messages;
    }
    else {
        mx_push_back(&chat->messages, message);
    }

    remove_chat(chat, all_chats_list_store);
    remove_chat(chat, visible_chats_list_store);
    add_chat_sorted(chat);

    if (chat->selected) {
        GtkListBoxRow *added_row = gtk_list_box_get_row_at_index(
                get_list_box(PERSONAL_CHAT_LIST_BOX_ID),
                0
        );
        set_chat_list_box_row_selected_style(added_row);
    }
}

void add_message_to_selected_chat(void) {
    char *message_text = get_entry_text(CHAT_MESSAGE_ENTRY_ID);
    if (strlen(message_text) > 0) {
        Message *message = create_message(
                message_text,
                true,
                get_current_time_millis()
        );

        guint selected_chat_index;
        get_selected_chat_index(&selected_chat_index);

        Chat *chat = get_list_store_item_by_index(all_chats_list_store,
                                                  selected_chat_index);
        if (chat->searching && chat->messages == NULL) {
            uint32_t other_user_id = chat->id;
            chat->id = rq_create_chat(chat->name, user_id, 
                                              serverAddress, Port);
            rq_add_user_to_chat(user_id, chat->id, serverAddress, Port);
            rq_add_user_to_chat(other_user_id, chat->id, serverAddress, Port);
            chat->searching = false;
            delete_searched_chats();
            show_chats_i_am_in();
            GtkEntry *search_entry = GTK_ENTRY(gtk_builder_get_object(Builder, SEARCH_CHAT_ENTRY_ID));
            gtk_entry_set_text(search_entry, "");
        }

        Message *previous_message = (Message *)mx_get_last_element(
                chat->messages);

        add_message(selected_chat_index, message);
        add_messages_list_box_row(message, previous_message);
        g_timeout_add(50, scroll_window_to_bottom,
                      CHAT_MESSAGES_SCROLLED_WINDOW_ID);
        set_entry_text(CHAT_MESSAGE_ENTRY_ID, "");
    }
}
