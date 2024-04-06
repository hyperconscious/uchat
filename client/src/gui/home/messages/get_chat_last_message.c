#include "home.h"

Message *get_chat_last_message(Chat *chat) {
    int messages_count = mx_list_size(chat->messages);
    return mx_get_element_by_index(chat->messages, messages_count - 1);
}
