#include "handle_requests.h"

void handle_edit_message(int client_socket, sqlite3 *db) 
{
    t_packet sender_id_packet;
    t_packet msg_id_packet;
    t_packet msg_text_packet;
    if(!receive_packet(client_socket, &sender_id_packet)) return;
    if(!receive_packet(client_socket, &msg_id_packet)) return;
    if(!receive_packet(client_socket, &msg_text_packet)) return;

    mx_edit_message(db, msg_id_packet.u_payload.uint32_data, msg_text_packet.u_payload.s_string.data);

    free_packet(&sender_id_packet);
    free_packet(&msg_id_packet);
    free_packet(&msg_text_packet);
}

