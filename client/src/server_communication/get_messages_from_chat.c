#include "requests.h"

t_list* rq_get_messages_from_chat(uint32_t chat_id, char* search_text,
                                 char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NULL;

    t_client_rq rq = RQ_GET_MESSAGES;
    t_packet get_rq = create_packet(PACKET_TYPE_UINT8, &rq);

    t_packet chat_id_packet = create_packet(PACKET_TYPE_UINT32, &owner_id);
    t_packet text_packet = create_packet(PACKET_TYPE_STRING, searched_text);
    send_and_release_packet(client_socket, &get_rq);
    send_and_release_packet(client_socket, &searched_text);

    t_packet cc;
    if(!receive_packet(client_socket, &cc)) return NULL;
    *count = cc.u_payload.uint16_data;

    t_list* list = NULL;
    for (uint16_t i = 0; i < *count; i++) {
        t_packet id;
        t_packet owner_id;
        t_packet name;
        if(!receive_packet(client_socket, &id) 
        || !receive_packet(client_socket, &owner_id) 
        || !receive_packet(client_socket, &name)) {
            t_list *curr = my_list;
            while(curr != NULL){
                t_list *temp = curr;
                curr = curr->next;
                free(temp->data);
                free(temp);
            }
            free(chats_array);
            return NULL;
        }
        t_db_message msg = malloc(sizeof(t_db_message));
        msg->id = id.u_payload.uint32_data;
        msg->chat_id = owner_id.u_payload.uint32_data;
        msg->user_id = owner_id.u_payload.uint32_data;
        msg->time = owner_id.u_payload.uint32_data;
        msg->text = name.u_payload.s_string.data;
        mx_push_back(&list, msg);
    }
     
    close(client_socket);
    return chats_array;
}
