#include "requests.h"

uint32_t rq_remove_chat(uint32_t chat_id, char* server_address, int port) 
{
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return 0;

    t_client_rq rq = RQ_REM_CHAT;
    t_packet rem_chat_rq = create_packet(PACKET_TYPE_UINT8, &rq);

    t_packet chat_id_p = create_packet(PACKET_TYPE_UINT32, &chat_id);
    send_and_release_packet(client_socket, &rem_chat_rq);
    send_and_release_packet(client_socket, &chat_id_p);

    close(client_socket);
    return 0;
} 
