#include "requests.h"

uint32_t rq_edit_msg(uint32_t msg_id, char* msg_text, char* server_address, int port) 
{
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return 0;

    t_client_rq rq = RQ_EDIT_MSG;
    t_packet rem_chat_rq = create_packet(PACKET_TYPE_UINT8, &rq);

    t_packet msg_id_p = create_packet(PACKET_TYPE_UINT32, &msg_id);
    t_packet msg_text_p = create_packet(PACKET_TYPE_STRING, msg_text);
    
    send_and_release_packet(client_socket, &rem_chat_rq);
    send_and_release_packet(client_socket, &msg_id_p);
    send_and_release_packet(client_socket, &msg_text_p);

    close(client_socket);
    return 0;
} 
