#include "handle_requests.h"

void handle_add_chat(int client_socket) {
    t_packet owner_id_packet = receive_packet(client_socket);
    t_packet chat_name_packet = receive_packet(client_socket);

    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open(DATABASE, &db);
    mx_init_add_chat(db, &stmt);
    printf("%s = %u", chat_name_packet.u_payload.s_string.data,
            owner_id_packet.u_payload.uint32_data);
    int chat_id = mx_add_chat(stmt, 
                              chat_name_packet.u_payload.s_string.data, 
                              owner_id_packet.u_payload.uint32_data);
    printf(" %d\n", chat_id);
    t_packet chat_id_packet = create_packet(PACKET_TYPE_UINT32, &chat_id);
    send_and_release_packet(client_socket, &chat_id_packet);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free_packet(&owner_id_packet);
    free_packet(&chat_name_packet);
}


