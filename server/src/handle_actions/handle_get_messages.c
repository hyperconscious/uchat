#include "handle_requests.h"

void handle_get_messages(int client_socket){
    t_packet chat_id;
    t_packet text_to_search;
    if(!receive_packet(client_socket, &chat_id)) return;

  /*  if(!receive_packet(client_socket, &text_to_search)) {
        printf("\nhihi\n");
        return;
    }*/
    (void)text_to_search;
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    int count = 0;
    t_db_message *msgs = NULL;
    mx_get_last_messages(db, chat_id.u_payload.uint32_data,
                            "", -1,
                            &msgs, &count);
    sqlite3_close(db);
    t_packet count_of_msgs = create_packet(PACKET_TYPE_UINT32, &count);
    send_and_release_packet(client_socket, &count_of_msgs);
    if (msgs) {
        for (int i = 0; i < count; ++i) {
            t_packet msg_id = create_packet(PACKET_TYPE_UINT32, &(msgs + i)->id);
            t_packet text = create_packet(PACKET_TYPE_STRING, (msgs + i)->text);
            t_packet time = create_packet(PACKET_TYPE_STRING, (msgs + i)->time);
            t_packet chat_id_r = create_packet(PACKET_TYPE_UINT32, &(msgs + i)->chat_id);
            t_packet user_id = create_packet(PACKET_TYPE_UINT32, &(msgs + i)->user_id);
            t_packet is_readed = create_packet(PACKET_TYPE_UINT8, &(msgs + i)->is_readed);

            send_and_release_packet(client_socket, &msg_id);
            send_and_release_packet(client_socket, &text);
            send_and_release_packet(client_socket, &time);
            send_and_release_packet(client_socket, &chat_id_r);
            send_and_release_packet(client_socket, &user_id);
            send_and_release_packet(client_socket, &is_readed);
        }
        free(msgs);
    }
    free_packet(&chat_id);
    free_packet(&text_to_search);
    return;
}

