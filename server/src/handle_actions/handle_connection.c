#include "handle_requests.h"

void handle_connection(int client_socket) {
    t_packet heart;
    printf("1");
    if(!receive_packet(client_socket, &heart)) return;
        printf("%hu", heart.u_payload.uint8_data);

    t_packet response = create_packet(PACKET_TYPE_UINT8,
                                      &(t_client_status_code){SUCCESS});
    send_and_release_packet(client_socket, &response);
}
