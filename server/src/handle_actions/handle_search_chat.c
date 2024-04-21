#include "handle_requests.h"

void handle_search_chat(int client_socket){

    t_packet name = receive_packet(client_socket);
    if(name.type != PACKET_TYPE_STRING) {
        fprintf(stderr, "Failed to receive packet from client\n");
        free_packet(&name);
        return;
    }
    char* chat_name_to_search = name.u_payload.s_string.data;
   
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    uint16_t count = 0;
    int *users = mx_find_users_by_login(db, chat_name_to_search, &count);

    if (users) {
        t_packet count_of_logins = create_packet(PACKET_TYPE_UINT16, &count);
        send_and_release_packet(client_socket, &count_of_logins);
        for (uint16_t i = 0; i < count; ++i) {
            char* login = mx_get_login_by_id(db, users[i]);
            t_packet login_to_send = create_packet(PACKET_TYPE_STRING, login);
            send_and_release_packet(client_socket, &login_to_send);
            free(login);
        }
        free(users);
    }
    sqlite3_close(db);
    free_packet(&name);
    return;
}
