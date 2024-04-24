#include "home.h"

t_list *get_chats(void) {
  /*  Chat *chat1 = create_chat(0, "client/src/gui/layout/img/ic_person.png",
                              "My notes", NULL, 0, false, 1712957612439);*/
//    Chat *chat2 = create_chat(0, "client/src/gui/layout/img/ic_person2.png",
//                              "Amanda", NULL, 0, false, 1712957612439);
//    Chat *chat3 = create_chat(0, "client/src/gui/layout/img/ic_person.png",
//                              "Yuriy", NULL, 0, false, 1712957612439);

    t_list *chats = NULL;//= mx_create_node(chat1);
//    mx_push_back(&chats, chat2);
//    mx_push_back(&chats, chat3);
    uint16_t count = 0;
    t_db_chat *my_chats = rq_get_chats(Client->id, &count, serverAddress, Port);
    for (uint16_t i = 0; i < count; i++) {
        char* chat_name = (my_chats + i)->owner_id == Client->id 
                          ? (my_chats + i)->name
                          : rq_get_login_by_id((my_chats + i)->owner_id,
                                               serverAddress, Port);
        t_list *msgs = rq_get_messages_from_chat((my_chats +i)->id, "",
                                                 serverAddress, Port);
        t_list *curr = msgs;
        t_list *res = NULL;
        while(curr != NULL){
            /* ui   printf("0.%lld (%s)\n", convert_to_epoch(((t_db_message
                                                 *)curr->data)->time),
                        convert_millis_to_hour_and_minute(convert_to_epoch(((t_db_message
                                                 *)curr->data)->time)));*/
            Message *msg = create_message(((t_db_message*)curr->data)->text,
                                     ((t_db_message *)curr->data)->user_id ==
                                     Client->id,
                                     convert_to_epoch(((t_db_message
                                                 *)curr->data)->time));
             /*   printf("1.%s (%s)\n", msg->text,
                        convert_millis_to_hour_and_minute(msg->time_in_millis));*/
            free(((t_db_message*)curr->data)->text);
            free(((t_db_message*)curr->data)->time);
            curr = curr->next;
            mx_push_back(&res, msg);
        }
        Chat *chat = create_chat((my_chats + i)->id, NULL, chat_name,
                                 res, 0, false, (my_chats +i)->is_private,
                                 convert_to_epoch((my_chats + i)->creation_time));
        free((my_chats + i)->name);
        free((my_chats + i)->creation_time);
        mx_push_back(&chats, chat);
    }
    free(my_chats);
    return chats;
}
