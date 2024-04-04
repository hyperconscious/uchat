#include "home.h"

void on_home_window_show(void) {
    Chat chat;
    chat.image_path = "client/src/gui/layout/img/ic_person.png";
    chat.name = "John";
    chat.last_message = "Hi. How are you?";
    chat.unread_message_count = 2;

    for (int i = 0; i < 3; i++) {
        create_new_chat_list_item(chat);
    }
}

void on_chat_list_item_select(void) {
    set_selected_chat_style();
}
