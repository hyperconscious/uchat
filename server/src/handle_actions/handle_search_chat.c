#include "handle_requests.h"

void handle_search_chat(int client_socket){

    t_packet name;
    if(!receive_packet(client_socket, &name)) return;
    if(name.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&name);
        return;
    }
    char* chat_name_to_search = name.u_payload.s_string.data;
  
    uint16_t count = 0;
    uint16_t sz = 0;
    t_db_chat* chats = NULL;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_stmt *stmt_u_id;
    sqlite3_open(DATABASE, &db);
    mx_init_get_chats_by_name(db, &stmt);
    mx_init_find_id_by_user(db, &stmt_u_id);

    mx_get_chats_by_name(stmt, chat_name_to_search, 15, &chats, &count);
    char** users = mx_find_users_by_login(db, 15, chat_name_to_search, &sz);
    t_packet count_arr = create_packet(PACKET_TYPE_UINT16, &(uint16_t){sz +
            count});
    sqlite3_finalize(stmt);
    send_and_release_packet(client_socket, &count_arr);
    for (uint16_t i = 0; i < count + sz; ++i) {
        if (i < count) {
            t_packet chat_id = create_packet(PACKET_TYPE_UINT32, &chats[i].id);
            t_packet chat_owner_id = create_packet(PACKET_TYPE_UINT32,
                                                   &chats[i].owner_id);
            t_packet chat_name = create_packet(PACKET_TYPE_STRING, chats[i].name);
            send_and_release_packet(client_socket, &chat_id);
            send_and_release_packet(client_socket, &chat_owner_id);
            send_and_release_packet(client_socket, &chat_name);
            continue;
        } 
        t_packet chat_id = create_packet(PACKET_TYPE_UINT32, &(uint32_t){0});
        uint32_t owner_id = mx_find_id_by_user(stmt_u_id, users[i - count]);
        t_packet chat_owner_id = create_packet(PACKET_TYPE_UINT32, &owner_id);
        t_packet chat_name = create_packet(PACKET_TYPE_STRING, users[i- count]);
        send_and_release_packet(client_socket, &chat_id);
        send_and_release_packet(client_socket, &chat_owner_id);
        send_and_release_packet(client_socket, &chat_name);
    }
    sqlite3_finalize(stmt_u_id);
    sqlite3_close(db);
    free(chats);
    free(users);
    free_packet(&name);
    return;
}
