#include "handle_requests.h"

void handle_get_chats(int client_socket){
    t_packet owner_id_packet = receive_packet(client_socket);
   
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    sqlite3_stmt *stmt;
    mx_init_get_chats_by_user_id(db, &stmt);
    uint16_t count = 0;
    t_db_chat *chats = NULL;
    mx_get_chats_by_user_id(stmt, owner_id_packet.u_payload.uint32_data,
                            -1, &chats, &count);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    t_packet count_of_chats = create_packet(PACKET_TYPE_UINT32, &count);
    send_and_release_packet(client_socket, &count_of_chats);
    if (chats) {
        for (uint16_t i = 0; i < count; ++i) {
            t_packet chat_id = create_packet(PACKET_TYPE_UINT32, &(chats + i)->id);
            t_packet chat_owner_id = create_packet(PACKET_TYPE_UINT32,
                                                   &(chats + i)->owner_id);
            t_packet chat_name = create_packet(PACKET_TYPE_STRING, (chats + i)->name);
            send_and_release_packet(client_socket, &chat_id);
            send_and_release_packet(client_socket, &chat_owner_id);
            send_and_release_packet(client_socket, &chat_name);
        }
        free(chats);
    }
    free_packet(&owner_id_packet);
    return;
}
    
