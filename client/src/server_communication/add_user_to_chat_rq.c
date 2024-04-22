#include "requests.h"

void rq_add_user_to_chat(uint32_t chat_id, uint32_t user_id, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return;

    t_client_rq rq = RQ_ADD_USER_TO_CHAT;
    t_packet send_rq = create_packet(PACKET_TYPE_UINT8, &rq);

    t_packet chat_id_packet = create_packet(PACKET_TYPE_UINT32, &chat_id);
    t_packet user_id_packet = create_packet(PACKET_TYPE_UINT32, &user_id);
    send_and_release_packet(client_socket, &send_rq);
    send_and_release_packet(client_socket, &chat_id_packet);
    send_and_release_packet(client_socket, &user_id_packet);

    //TODO: receive response to show if add was succesful    
    close(client_socket);
}
