#include "requests.h"

char* rq_get_login_by_id(uint32_t id, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return 0;

    t_client_rq rq = RQ_GET_LOGIN_BY_ID;
    t_packet packet_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet user_id = create_packet(PACKET_TYPE_UINT32, &id);
    send_and_release_packet(client_socket, &packet_rq);
    send_and_release_packet(client_socket, &user_id);

    t_packet login;
    if(!receive_packet(client_socket, &login)) return NULL;
    close(client_socket);
    return login.u_payload.s_string.data; 
} 
