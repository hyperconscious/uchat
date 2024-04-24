#include "requests.h"

void rq_delete_message(uint32_t id, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return;

    t_client_rq rq = RQ_DELETE_MESSAGE;
    t_packet packet_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet user_id = create_packet(PACKET_TYPE_UINT32, &id);
    send_and_release_packet(client_socket, &packet_rq);
    send_and_release_packet(client_socket, &user_id);

    
    close(client_socket);
} 
