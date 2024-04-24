#include "core.h"

gboolean timer_callback() {
    if(!Client->name) return TRUE;
    show_internet_connection_status(WAITING);
  /*  int socket = create_and_connect_socket(serverAddress, Port);
    if(socket != -1){
        show_internet_connection_status(AVAIBLE);
    printf("1");


        t_client_rq rq = CONNECTION;
        t_packet request = create_packet(PACKET_TYPE_UINT8, &rq);
        t_packet heart = create_packet(PACKET_TYPE_UINT32,
                                      &(uint32_t){3000});
        send_and_release_packet(socket, &request);
        send_and_release_packet(socket, &heart);
    printf("1");
        t_packet response;
        if(!receive_packet(socket, &response))
        {
    printf("1");
            show_internet_connection_status(UNAVAIBLE);
           pthread_t thread = create_thread(handle_connection_lost, NULL);
            join_thread(thread, NULL);
        }
    printf("1");
    }*/
    return TRUE;
}

