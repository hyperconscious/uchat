#include "handle_login.h"

void handle_login(int client_socket) {
    t_packet user = receive_packet(client_socket);
    t_packet pass = receive_packet(client_socket);

    if(user.type != PACKET_TYPE_STRING || pass.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&user);
        free_packet(&pass);
        return;
    }

    char* username = user.u_payload.s_string.data;
    char* password = pass.u_payload.s_string.data;

    t_db_info *info;
    mx_init_db_info(DATABASE, &info);
    int id = mx_find_id_by_login(info, username);
    t_client_status_code result_code = SUCCESS_LOGIN;

    if (id < 0)
    {
        result_code = LOGIN_DOESNT_EXIST;
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    else if (mx_check_password(info, id, password) == 100) {
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        t_packet packet_id = create_packet(PACKET_TYPE_UINT32, &id);
        send_and_release_packet(client_socket, &packet_code);
        send_and_release_packet(client_socket, &packet_id);
    } else {
        result_code = WRONG_PASSWORD; 
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    mx_destroy_db_info(&info);
    free_packet(&user);
    free_packet(&pass);
}

