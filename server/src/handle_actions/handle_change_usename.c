#include "handle_requests.h"

void handle_change_username(int client_socket) {
    t_packet old_user_packet = receive_packet(client_socket);
    t_packet new_user_packet = receive_packet(client_socket);

    //char* old_username = old_user_packet.u_payload.s_string.;
   // char* new_username = new_user_packet.u_payload.s_string;

    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_change_username(db, old_user_packet.u_payload.uint32_data, new_user_packet.u_payload.s_string.data);
 
    sqlite3_close(db);
    free_packet(&old_user_packet);
    free_packet(&new_user_packet);
}

