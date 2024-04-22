#include "requests.h"

void change_username_rq(uint32_t id, char* new_username, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return;

    t_client_rq rq = RQ_CHANGE_USERNAME;
    t_packet send_rq = create_packet(PACKET_TYPE_UINT8, &rq);

    t_packet old_user_packet = create_packet(PACKET_TYPE_UINT32, &id);
    t_packet new_user_packet = create_packet(PACKET_TYPE_STRING, new_username);
    send_and_release_packet(client_socket, &send_rq);
    send_and_release_packet(client_socket, &old_user_packet);
    send_and_release_packet(client_socket, &new_user_packet);

    close(client_socket);
}

