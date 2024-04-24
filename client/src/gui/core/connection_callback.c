#include "core.h"

gboolean timer_callback() {
    int socket = create_and_connect_socket(serverAddress, Port);
    if(socket != -1){
        t_client_rq rq = CONNECTION;
        t_packet request = create_packet(PACKET_TYPE_UINT8, &rq);
        t_packet heart = create_packet(PACKET_TYPE_UINT8,
                                      &(t_client_status_code){SUCCESS});
        send_and_release_packet(socket, &request);
        send_and_release_packet(socket, &heart);
        t_packet response;
        if(!receive_packet(socket, &response)) {
            show_internet_connection_status(WAITING);
            /* pthread_t thread = create_thread(handle_connection_lost, NULL);
            join_thread(thread, NULL);*/
        } else {
            show_internet_connection_status(AVAIBLE);
        }
    } else {
            show_internet_connection_status(UNAVAIBLE);
    }
    close(socket);
    return TRUE;
}

