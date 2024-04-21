#include "handle_requests.h"

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

    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open(DATABASE, &db);

    mx_init_find_id_by_user(db, &stmt);
    int /*uint32_t*/ id = mx_find_id_by_user(stmt, username);
    sqlite3_finalize(stmt);
    t_client_status_code result_code = SUCCESS_LOGIN;
    mx_init_check_password(db, &stmt);
    if (id < 0)
    {
        result_code = LOGIN_DOESNT_EXIST;
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    else if (mx_check_password(stmt, id, password) == 100) {
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        t_packet packet_id = create_packet(PACKET_TYPE_UINT32, &id);
        send_and_release_packet(client_socket, &packet_code);
        send_and_release_packet(client_socket, &packet_id);
    } else {
        result_code = WRONG_PASSWORD; 
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free_packet(&user);
    free_packet(&pass);
}

