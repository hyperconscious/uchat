#include "handle_requests.h"
#include <time.h>


void handle_add_user_to_chat(int client_socket, sqlite3 *db) {
    t_packet chat_id_packet;
    t_packet user_id_packet;
    if(!receive_packet(client_socket, &chat_id_packet)) return;
    if(!receive_packet(client_socket, &user_id_packet)) return;

    sqlite3_busy_timeout(db, 5000);

    sqlite3_stmt *stmt;
    mx_init_add_user_to_chat(db, &stmt);
    mx_add_user_to_chat(stmt, user_id_packet.u_payload.uint32_data,
                        chat_id_packet.u_payload.uint32_data);
    sqlite3_finalize(stmt);
    free_packet(&chat_id_packet);
    free_packet(&user_id_packet);
}
