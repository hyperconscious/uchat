#include "handle_requests.h"

void handle_connection(int client_socket) {
    t_packet heart;
    if(!receive_packet(client_socket, &heart)) return;

    t_packet response = create_packet(PACKET_TYPE_UINT8,
                                      &(t_client_status_code){SUCCESS});
    send_and_release_packet(client_socket, &response);
}
