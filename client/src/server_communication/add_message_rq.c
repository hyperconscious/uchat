#include "requests.h"

int rq_add_message(uint32_t user_id, uint32_t chat_id, char* text, 
                    char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return -1;

    t_client_rq rq = RQ_ADD_MESSAGE;
    t_packet send_rq = create_packet(PACKET_TYPE_UINT8, &rq);

    t_packet user_id_packet = create_packet(PACKET_TYPE_UINT32, &user_id);
    t_packet chat_id_packet = create_packet(PACKET_TYPE_UINT32, &chat_id);
    t_packet text_packet = create_packet(PACKET_TYPE_STRING, text);
    send_and_release_packet(client_socket, &send_rq);
    send_and_release_packet(client_socket, &user_id_packet);
    send_and_release_packet(client_socket, &chat_id_packet);
    send_and_release_packet(client_socket, &text_packet);

    t_packet message_id;
    if(!receive_packet(client_socket, &message_id)) return -1;
    close(client_socket);
    return message_id.u_payload.uint32_data;
}

