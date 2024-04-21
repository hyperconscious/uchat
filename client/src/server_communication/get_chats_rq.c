#include "requests.h"

t_chat** rq_get_chats(uint32_t owner_id, uint16_t *count, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NULL;

    t_client_rq rq = RQ_GET_CHATS;
    t_packet get_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet owner_id_packet = create_packet(PACKET_TYPE_UINT32, &owner_id);
    send_and_release_packet(client_socket, &get_rq);
    send_and_release_packet(client_socket, &owner_id_packet);

    *count = receive_packet(client_socket).u_payload.uint16_data;
    t_chat **chats_array = malloc(*count * sizeof(t_chat*));
    for (uint16_t i = 0; i < *count; i++) {
        chats_array[i]->id = receive_packet(client_socket).u_payload.uint32_data;
        chats_array[i]->owner_id = receive_packet(client_socket).u_payload.uint32_data;
        chats_array[i]->name =receive_packet(client_socket).u_payload.s_string.data;
    }
    
    close(client_socket);
    return chats_array;
}

