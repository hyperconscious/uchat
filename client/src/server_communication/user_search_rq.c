#include "requests.h"

t_db_chat* rq_search_chats(char* searching_chat, uint16_t *count,
                           char* server_address, int port){
    if(strlen(searching_chat) == 0) return NULL;
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NULL;

    t_client_rq rq = RQ_SEARCH_CHAT;
    t_packet search_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet chat_name_to_search = create_packet(PACKET_TYPE_STRING,
                                                    searching_chat);
    send_and_release_packet(client_socket, &search_rq);
    send_and_release_packet(client_socket, &chat_name_to_search);

    t_packet cc;
    if(!receive_packet(client_socket, &cc)) {
        fprintf(stderr, "search failed");
        return NULL;
    }
    *count = cc.u_payload.uint16_data;
    t_db_chat *chats_array = malloc((*count) * sizeof(t_db_chat));
    for (uint16_t i = 0; i < *count; i++) {
        t_packet id;
        t_packet owner_id;
        t_packet name;
        if(!receive_packet(client_socket, &id) 
        || !receive_packet(client_socket, &owner_id) 
        || !receive_packet(client_socket, &name)) {
            fprintf(stderr, "search failed");
            for(uint16_t j = 0; j < i; j++){
                free(chats_array[j].name);
            }
            free(chats_array);
            return NULL;
        }
        (chats_array + i)->id = id.u_payload.uint32_data;
        (chats_array + i)->owner_id = owner_id.u_payload.uint32_data;
        (chats_array + i)->name = name.u_payload.s_string.data;
    }
    
    close(client_socket);
    return chats_array;
}
