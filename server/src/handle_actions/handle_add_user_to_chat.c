#include "handle_requests.h"

void handle_add_user_to_chat(int client_socket) {
    t_packet chat_id_packet = receive_packet(client_socket);
    t_packet user_id_packet = receive_packet(client_socket);

    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open(DATABASE, &db);
    sqlite3_busy_timeout(db, 20000);
    mx_init_add_user_to_chat(db, &stmt);
    mx_add_user_to_chat(stmt, user_id_packet.u_payload.uint32_data,
                        chat_id_packet.u_payload.uint32_data);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free_packet(&chat_id_packet);
    free_packet(&user_id_packet);
}
