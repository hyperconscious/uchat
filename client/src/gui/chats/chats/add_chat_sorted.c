#include "home.h"

static int compare_chats_last_message_time(const void *a,
                                           const void *b,
                                           void *user_data) {
   /* if (user_data == NULL) {}

    Chat *first_chat = (Chat *)a;
    Chat *second_chat = (Chat *)b;

    if (first_chat->messages != NULL && second_chat->messages != NULL) {
        Message *first_chat_last_message = get_chat_last_message(first_chat);
        Message *second_chat_last_message = get_chat_last_message(second_chat);
        return second_chat_last_message->time_in_millis -
               first_chat_last_message->time_in_millis;
    }
    else if (first_chat->messages == NULL) {
        long long first_chat_creation_time = first_chat->creation_time_in_millis;
        Message *second_chat_last_message = get_chat_last_message(second_chat);
        return second_chat_last_message->time_in_millis -
               first_chat_creation_time;
    }
    else {
        long long second_chat_creation_time = second_chat->creation_time_in_millis;
        Message *first_chat_last_message = get_chat_last_message(first_chat);
        return second_chat_creation_time -
               first_chat_last_message->time_in_millis;
    }*/
    (void)a;
    (void)b;
    (void)user_data;
    return 1;
}

guint add_chat_sorted_all_list_store(Chat *chat) {
    return g_list_store_insert_sorted(
            all_chats_list_store,
            chat,
            compare_chats_last_message_time,
            NULL
    );
}

guint add_chat_sorted_all_list_store(Chat *chat) {
    return g_list_store_insert_sorted(
            all_chats_list_store,
            chat,
            compare_chats_last_message_time,
            NULL
    );
}

guint add_chat_sorted_to_visible_list_store(Chat *chat) {
    return g_list_store_insert_sorted(
            visible_chats_list_store,
            chat,
            compare_chats_last_message_time,
            NULL
    );
}

void add_chat_sorted(Chat *chat) {
    add_chat_sorted_to_visible_list_store(chat);
    g_list_store_insert_sorted(
            all_chats_list_store,
            chat,
            compare_chats_last_message_time,
            NULL
    );
}
