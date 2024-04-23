#include "handle_requests.h"

void handle_add_message(int client_socket) {
    t_packet sender_id_packet;
    t_packet chat_id_packet;
    t_packet message_text_packet;
    if(!receive_packet(client_socket, &sender_id_packet)) return;
    if(!receive_packet(client_socket, &chat_id_packet)) return;
    if(!receive_packet(client_socket, &message_text_packet)) return;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open(DATABASE, &db);
    mx_init_add_message(db, &stmt);
    mx_add_message(stmt, message_text_packet.u_payload.s_string.data, 
                   sender_id_packet.u_payload.uint32_data,
                   chat_id_packet.u_payload.uint32_data);
    uint32_t message_id = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    t_packet message_id_packet = create_packet(PACKET_TYPE_UINT32, &message_id);
    send_and_release_packet(client_socket, &message_id_packet);
    free_packet(&sender_id_packet);
    free_packet(&chat_id_packet);
    free_packet(&message_text_packet);
}
