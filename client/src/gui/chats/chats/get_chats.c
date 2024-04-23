#include "home.h"

t_list *get_chats(void) {
    Chat *chat1 = create_chat(0, NULL, "My notes", NULL, 0, false, 1712957612439);
    t_list *chats = mx_create_node(chat1);
    uint16_t count = 0;
    t_db_chat *my_chats = rq_get_chats(user_id, &count, serverAddress, Port);
    for (uint16_t i = 0; i < count; i++) {
        char* chat_name = (my_chats + i)->owner_id == user_id 
                          ? (my_chats + i)->name
                          : rq_get_login_by_id((my_chats + i)->owner_id,
                                               serverAddress, Port);
        t_list *msgs = rq_get_messages_from_chat((my_chats +i)->id, "",
                                                 serverAddress, Port);
        t_list *curr = msgs;
        t_list *res = NULL;
        while(curr != NULL){
            Message *msg = create_message(((t_db_message*)curr->data)->text,
                                     ((t_db_message *)curr->data)->user_id != user_id,
                                     convert_to_epoch(((t_db_message
                                                 *)curr->data)->time));
            curr = curr->next;
            mx_push_back(&res, msg);
        }

        Chat *chat = create_chat((my_chats + i)->id, NULL, chat_name,
                                 res, 0, false,
                                 convert_to_epoch((my_chats + i)->creation_time));
        mx_push_back(&chats, chat);
    }
    free(my_chats);
    return chats;
}
