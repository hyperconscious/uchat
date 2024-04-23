#include "handle_requests.h"

void handle_get_login_by_id(int client_socket) {
    t_packet user_id_packet;
    if(!receive_packet(client_socket, &user_id_packet)) return;

    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    char* login = mx_get_login_by_id(db, user_id_packet.u_payload.uint32_data);
    sqlite3_close(db);

    t_packet login_packet = create_packet(PACKET_TYPE_STRING, login);
    send_and_release_packet(client_socket, &login_packet);
    free_packet(&user_id_packet);
}
