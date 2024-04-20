#include "home.h"

t_list *get_chats(void) {
    Chat *chat1 = create_chat(0, "client/src/gui/layout/img/ic_person2.png",
                              "Doe", NULL, 10, false, 1712957612439);

    Message *chat2_message1 = create_message("Hi", false, 1712957652439);
    Message *chat2_message2 = create_message("How are you?", true,
                                             1712957682439);
    Message *chat2_message3 = create_message("I'm OK", false, 1712957682439);
    t_list *chat2_messages = mx_create_node(chat2_message1);
    mx_push_back(&chat2_messages, chat2_message2);
    mx_push_back(&chat2_messages, chat2_message3);
    Chat *chat2 = create_chat(1, NULL, "Jack", chat2_messages, 100, false,
                              1712910640569);

    Message *chat3_message1 = create_message("Good morning!", true,
                                             1681275262439);
    Message *chat3_message2 = create_message("How's it going!", false,
                                             1712957672439);
    Message *chat3_message3 = create_message("I'm fine", true, 1712957682439);
    t_list *chat3_messages = mx_create_node(chat3_message1);
    mx_push_back(&chat3_messages, chat3_message2);
    mx_push_back(&chat3_messages, chat3_message3);
    Chat *chat3 = create_chat(2, "client/src/gui/layout/img/ic_person.png",
                              "John", chat3_messages, 0, false, 1712910640569);

    t_list *chats = mx_create_node(chat1);
    mx_push_back(&chats, chat2);
    mx_push_back(&chats, chat3);

    return chats;
}
