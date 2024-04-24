#include "handle_requests.h"

void handle_remove_chat(int client_socket, sqlite3 *db) 
{
    t_packet sender_id_packet;
    t_packet msg_id_packet;
    if(!receive_packet(client_socket, &sender_id_packet)) return;
    if(!receive_packet(client_socket, &msg_id_packet)) return;

    mx_sub_chat(db, msg_id_packet.u_payload.uint32_data);
    free_packet(&sender_id_packet);
    free_packet(&msg_id_packet);
}
