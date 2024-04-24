#include "handle_requests.h"



void handle_delete_message(int client_socket, sqlite3 *db) {
    t_packet message_id_packet = {0};

    if(!receive_packet(client_socket, &message_id_packet)) return;
    mx_remove_message(db, message_id_packet.u_payload.uint32_data);
    free_packet(&message_id_packet);
    return;

}
