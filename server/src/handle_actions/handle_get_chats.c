#include "handle_requests.h"

void handle_get_chats(int client_socket){
    t_packet owner_id_packet = receive_packet(client_socket);
   
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    uint16_t count = 0;
    char **chats = mx_get_chat_names(db, owner_id_packet.u_payload.uint32_data,
                                   &count);

    if (chats) {
        t_packet count_of_chats = create_packet(PACKET_TYPE_UINT16, &count);
        send_and_release_packet(client_socket, &count_of_chats);
        for (uint16_t i = 0; i < count; ++i) {
            t_packet chat_to_send = create_packet(PACKET_TYPE_STRING, chats[i]);
            send_and_release_packet(client_socket, &chat_to_send);
            free(chats[i]);
        }
        free(chats);
    }
    sqlite3_close(db);
    free_packet(&owner_id_packet);
    return;
}
    
