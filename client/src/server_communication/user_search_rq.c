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

    *count= receive_packet(client_socket).u_payload.uint16_data;
    t_db_chat *chats_array = malloc((*count) * sizeof(t_db_chat));
    for (uint16_t i = 0; i < *count; i++) {
        (chats_array + i)->id = receive_packet(client_socket).u_payload.uint32_data;
        (chats_array + i)->owner_id = receive_packet(client_socket).u_payload.uint32_data;
        (chats_array + i)->name =receive_packet(client_socket).u_payload.s_string.data;
    }
    
    close(client_socket);
    return chats_array;
}
