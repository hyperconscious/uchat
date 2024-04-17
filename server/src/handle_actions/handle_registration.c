#include "handle_registration.h"

void handle_sign_up(int client_socket) {
    t_packet user = receive_packet(client_socket);
    t_packet pass = receive_packet(client_socket);
    char* username = user.u_payload.s_string.data;
    char* password = pass.u_payload.s_string.data;

    if(user.type != PACKET_TYPE_STRING || pass.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&user);
        free_packet(&pass);
        return;
    }

    int id = -1; //uint32_t
    t_client_status_code result_code = SUCCESS_REGISTRATION;  
    t_db_info *info;
    
    mx_init_db_info(DATABASE, &info);
    if (mx_add_user(info, username, password, &id) == 0) {
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        t_packet packet_id = create_packet(PACKET_TYPE_UINT32, &id);
        send_and_release_packet(client_socket, &packet_code);
        send_and_release_packet(client_socket, &packet_id);
    } else {
        result_code = LOGIN_ALREADY_EXIST; 
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    mx_destroy_db_info(&info);
    free_packet(&user);
    free_packet(&pass);
}
