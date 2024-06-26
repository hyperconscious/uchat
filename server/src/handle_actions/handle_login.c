#include "handle_requests.h"

void handle_login(int client_socket, sqlite3 *db) {
    t_packet user;
    t_packet pass;
    if(!receive_packet(client_socket, &user)) return;
    if(!receive_packet(client_socket, &pass)) return;

    if(user.type != PACKET_TYPE_STRING || pass.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&user);
        free_packet(&pass);
        return;
    }

    char* username = user.u_payload.s_string.data;
    char* password = pass.u_payload.s_string.data;

    sqlite3_stmt *stmt1;
    sqlite3_stmt *stmt2;

    mx_init_find_id_by_user(db, &stmt1);
    int /*uint32_t*/ id = mx_find_id_by_user(stmt1, username);
    sqlite3_finalize(stmt1);
    t_client_status_code result_code = SUCCESS_LOGIN;
    mx_init_check_password(db, &stmt2);
    int res = mx_check_password(stmt2, username, password);
    
    if (id < 0)
    {
        result_code = LOGIN_DOESNT_EXIST;
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    else if (res == 1) {
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        t_packet packet_id = create_packet(PACKET_TYPE_UINT32, &id);
        send_and_release_packet(client_socket, &packet_code);
        send_and_release_packet(client_socket, &packet_id);
    } else {
        result_code = WRONG_PASSWORD; 
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    sqlite3_finalize(stmt2);
    free_packet(&user);
    free_packet(&pass);
}

