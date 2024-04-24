#include "handle_requests.h"

void handle_change_username(int client_socket, sqlite3 *db) {
    t_packet old_user_packet;
    t_packet new_user_packet;
    if(!receive_packet(client_socket, &old_user_packet)) return;
    if(!receive_packet(client_socket, &new_user_packet)) return;

    int res = mx_change_username(db, old_user_packet.u_payload.uint32_data,
                                 new_user_packet.u_payload.s_string.data);
    t_packet result = create_packet(PACKET_TYPE_UINT8, &res);
    send_and_release_packet(client_socket, &result);
 
    free_packet(&old_user_packet);
    free_packet(&new_user_packet);
}

