#include "handle_requests.h"

void handle_sign_up(int client_socket) {
    t_packet user;
    t_packet pass;
    t_packet lang;
    if(!receive_packet(client_socket, &user)) return;
    if(!receive_packet(client_socket, &pass)) return;
    if(!receive_packet(client_socket, &lang)) return;

    char* username = user.u_payload.s_string.data;
    char* password = pass.u_payload.s_string.data;
    uint16_t language = lang.u_payload.uint16_data;

    if(user.type != PACKET_TYPE_STRING || pass.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&user);
        free_packet(&pass);
        free_packet(&lang);

        return;
    }

    int id = -1; //uint32_t
    t_client_status_code result_code = SUCCESS_REGISTRATION;  

    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open(DATABASE, &db);
    mx_init_add_user(db, &stmt);
    int res = mx_add_user(stmt, username, password, language);
    sqlite3_finalize(stmt);
    
    if (res == 0) {
        id = sqlite3_last_insert_rowid(db);
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        t_packet packet_id = create_packet(PACKET_TYPE_UINT32, &id);
        send_and_release_packet(client_socket, &packet_code);
        send_and_release_packet(client_socket, &packet_id);
    } else /*if(res == SQLITE_CONSTRAINT)*/{
     //   printf("%d\n", res);
        result_code = LOGIN_ALREADY_EXIST; 
        t_packet packet_code = create_packet(PACKET_TYPE_UINT8, &result_code);
        send_and_release_packet(client_socket, &packet_code);
    }
    sqlite3_close(db);
    free_packet(&user);
    free_packet(&pass);
}
