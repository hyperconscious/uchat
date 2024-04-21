#include "handle_requests.h"
#include "handle_db_chat.h"

void handle_search_chat(int client_socket){

    t_packet name = receive_packet(client_socket);
    if(name.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&name);
        return;
    }
    char* chat_name_to_search = name.u_payload.s_string.data;
  
    
    uint16_t count = 0;
    t_db_chat* chats = NULL;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open(DATABASE, &db);
    mx_init_get_chats_by_name(db, &stmt);
    mx_get_chats_by_name(stmt, chat_name_to_search, 15, &chats, &count);
    t_packet count_of_logins = create_packet(PACKET_TYPE_UINT16, &count);
    send_and_release_packet(client_socket, &count_of_logins);
    for (uint16_t i = 0; i < count; ++i) {
        t_packet chat_id = create_packet(PACKET_TYPE_UINT32, &chats[i].id);
        t_packet chat_owner_id = create_packet(PACKET_TYPE_UINT32,
                                               &chats[i].owner_id);
        t_packet chat_name = create_packet(PACKET_TYPE_STRING, chats[i].name);
        send_and_release_packet(client_socket, &chat_id);
        send_and_release_packet(client_socket, &chat_owner_id);
        send_and_release_packet(client_socket, &chat_name);
        free(chats + i);
    }
    free(chats);
    sqlite3_close(db);
    free_packet(&name);
    return;
}
