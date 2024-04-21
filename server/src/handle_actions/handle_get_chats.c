#include "handle_requests.h"

void handle_get_chats(int client_socket){
    t_packet owner_id_packet = receive_packet(client_socket);
   
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    sqlite3_stmt *stmt;
    mx_init_get_chats_id_by_user_id(db, &stmt);
    uint16_t count = 0;
    t_chat **chats = NULL;
    mx_get_chats_by_user_id(stmt, owner_id_packet.u_payload.uint32_data,
                            -1, chats, &count);
    if (chats) {
        t_packet count_of_chats = create_packet(PACKET_TYPE_UINT16, &count);
        send_and_release_packet(client_socket, &count_of_chats);
        for (uint16_t i = 0; i < count; ++i) {
            t_packet chat_to_send = create_packet(PACKET_TYPE_CHAT, chats[i]);
            printf("sended chat");
            send_and_release_packet(client_socket, &chat_to_send);
            free(chats[i]);
        }
        free(chats);
    }
    sqlite3_close(db);
    free_packet(&owner_id_packet);
    return;
}
    
