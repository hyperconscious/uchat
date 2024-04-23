#include "handle_requests.h"

void handle_discover(int client_socket){
    t_packet id;
    if(!receive_packet(client_socket, &id)) return;
   
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);

    uint32_t lang = mx_get_lang_by_id(db, id.u_payload.uint32_data);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT id FROM user_data WHERE name == ?", -1, &stmt, 0);



    uint16_t count = 0;
    char **chats = mx_get_users_by_language (db, lang, &count);

    uint32_t found_id;
    if (chats) {
        t_packet count_of_chats = create_packet(PACKET_TYPE_UINT16, &count);
        send_and_release_packet(client_socket, &count_of_chats);
        for (uint16_t i = 0; i < count; ++i) {
            t_packet chat_to_send = create_packet(PACKET_TYPE_STRING, chats[i]);
            send_and_release_packet(client_socket, &chat_to_send);

            found_id = mx_get_user_id_by_login(stmt, chats[i]);

            t_packet id_to_send = create_packet(PACKET_TYPE_UINT32, &found_id);


            send_and_release_packet(client_socket, &id_to_send);


            free(chats[i]);


        }
        free(chats);
     

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free_packet(&id);
    return;
} 
    
