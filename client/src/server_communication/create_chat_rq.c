#include "requests.h"

uint32_t rq_create_chat(char* name, uint32_t owner_id, char* server_address, int port) {
    if(strlen(name) == 0) return 0;
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return 0;

    t_client_rq rq = RQ_ADD_CHAT;
    t_packet add_chat_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet owner_id_p = create_packet(PACKET_TYPE_UINT32, &owner_id);
    t_packet chat_name = create_packet(PACKET_TYPE_STRING, name);
    send_and_release_packet(client_socket, &add_chat_rq);
    send_and_release_packet(client_socket, &owner_id_p);
    send_and_release_packet(client_socket, &chat_name);

    t_packet chat_id;
    if(!receive_packet(client_socket, &chat_id)) return 0;
    close(client_socket);
    return chat_id.u_payload.uint32_data;
} 
