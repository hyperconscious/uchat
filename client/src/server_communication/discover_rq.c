#include "requests.h"

char** rq_discover(uint32_t id, uint16_t *count, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NULL;

    t_client_rq rq = RQ_DISCOVER;
    t_packet get_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet user_id = create_packet(PACKET_TYPE_UINT16, &id);
    send_and_release_packet(client_socket, &get_rq);
    send_and_release_packet(client_socket, &user_id);

    *count = receive_packet(client_socket).u_payload.uint16_data;
    char **chats_array = malloc(*count * sizeof(char*));
    for (uint16_t i = 0; i < *count; i++) {
        chats_array[i] = receive_packet(client_socket).u_payload.s_string.data;
    }
    
    close(client_socket);
    return chats_array; 
}

