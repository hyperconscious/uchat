#include "user_search_rq.h"

char** search_chats(char* searching_chat, uint16_t *count,  char* server_address, int port){
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

    *count = receive_packet(client_socket).u_payload.uint16_data;
    char **users_array = malloc(*count * sizeof(char*));
    for (uint16_t i = 0; i < *count; i++) {
        users_array[i] = receive_packet(client_socket).u_payload.s_string.data;
        printf("%s\n", users_array[i]);
    }
    
    close(client_socket);
    return users_array;
}
