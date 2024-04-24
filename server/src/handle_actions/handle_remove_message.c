#include "handle_requests.h"

void handle_remove_message(int client_socket, sqlite3 *db) 
{
    t_packet sender_id_packet;
    t_packet msg_id_packet;
    if(!receive_packet(client_socket, &sender_id_packet)) return;
    if(!receive_packet(client_socket, &msg_id_packet)) return;

    sqlite3_stmt *stmt;
    mx_init_sub_message(db, &stmt);
    mx_sub_message(stmt, msg_id_packet.u_payload.uint32_data);
    sqlite3_finalize(stmt);
    free_packet(&sender_id_packet);
    free_packet(&msg_id_packet);
}
