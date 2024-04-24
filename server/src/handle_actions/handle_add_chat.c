#include "handle_requests.h"

void handle_add_chat(int client_socket, sqlite3* db) {
    t_packet owner_id_packet;
    t_packet chat_name_packet;
    t_packet is_private;
    if(!receive_packet(client_socket, &owner_id_packet)) return;
    if(!receive_packet(client_socket, &chat_name_packet)) return;
    if(!receive_packet(client_socket, &is_private)) return;

    sqlite3_stmt *stmt;
    mx_init_add_chat(db, &stmt);
    mx_add_chat(stmt, chat_name_packet.u_payload.s_string.data, 
                owner_id_packet.u_payload.uint32_data);
    if(is_private.u_payload.uint8_data){
    } else
        printf("false");

    uint32_t chat_id = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    t_packet chat_id_packet = create_packet(PACKET_TYPE_UINT32, &chat_id);
    send_and_release_packet(client_socket, &chat_id_packet);
    free_packet(&owner_id_packet);
    free_packet(&chat_name_packet);
}

