#include "handle_search_chat.h"

void handle_search_chat(int client_socket){

    t_packet name = receive_packet(client_socket);
    if(name.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&name);
        return;
    }
    char* chat_name_to_search = name.u_payload.s_string.data;
    (void)chat_name_to_search;
    
    //t_list *result = mx_get_chats(chat_name_to_search);
    
   /* t_list *chat2_messages = mx_create_node("message");
    mx_push_back(&chat2_messages, "hi");
    mx_push_back(&chat2_messages, "den");*/

    
    free_packet(&name);
    return;
}
