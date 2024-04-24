#include "requests.h"

t_list* rq_get_messages_from_chat(uint32_t chat_id, char* search_text,
                                 char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NULL;

    t_client_rq rq = RQ_GET_MESSAGES;
    t_packet get_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    (void)search_text;
    t_packet chat_id_packet = create_packet(PACKET_TYPE_UINT32, &chat_id);
  /*  t_packet text_packet = create_packet(PACKET_TYPE_STRING, search_text);*/
    send_and_release_packet(client_socket, &get_rq);
    send_and_release_packet(client_socket, &chat_id_packet);
   // send_and_release_packet(client_socket, &text_packet);

    t_packet cc;
    if(!receive_packet(client_socket, &cc)) return NULL;
    int count = cc.u_payload.uint16_data;

    t_list* list = NULL;
    for (uint16_t i = 0; i < count; i++) {
        t_packet msg_id;
        t_packet text;
        t_packet time;
        t_packet chat_id;
        t_packet user_id;
        t_packet is_readed;
        if(!receive_packet(client_socket, &msg_id) 
        || !receive_packet(client_socket, &text) 
        || !receive_packet(client_socket, &time) 
        || !receive_packet(client_socket, &chat_id) 
        || !receive_packet(client_socket, &user_id) 
        || !receive_packet(client_socket, &is_readed)) {
            t_list *curr = list;
            while(curr != NULL){
                t_list *temp = curr;
                curr = curr->next;
                free(temp->data);
                free(temp);
            }
            return NULL;
        }
        t_db_message *msg = malloc(sizeof(t_db_message));
        msg->id = msg_id.u_payload.uint32_data;
        msg->chat_id = chat_id.u_payload.uint32_data;
        msg->user_id = user_id.u_payload.uint32_data;
        msg->time = strdup(time.u_payload.s_string.data);
        msg->text = strdup(text.u_payload.s_string.data);
        msg->is_readed = text.u_payload.uint8_data;
        mx_push_back(&list, msg);
        free_packet(&time);
        free_packet(&text);
    }
     
    close(client_socket);
    return list;
}
