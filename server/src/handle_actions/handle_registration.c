#include "handle_registration.h"

void handle_sign_up(int client_socket) {
    t_packet user = receive_packet(client_socket);
    t_packet pass = receive_packet(client_socket);

    if(user.type != PACKET_TYPE_STRING || pass.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        return;
    }

    char* username = user.u_payload.s_string.data;
    char* password = pass.u_payload.s_string.data;
    (void)username;
    (void)password;

    t_client_status_code result_code = SUCCESS_REGISTRATION; // LOGIN_ALREADY_EXIST or SUCCESS_REGISTRATION;
    t_packet packet_to_send = create_packet(PACKET_TYPE_UINT8, &result_code);
    send_and_release_packet(client_socket, &packet_to_send);

    free_packet(&user);
    free_packet(&pass);

}
