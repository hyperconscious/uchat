#include "handle_client.h"

void *handle_client(void *arg) {
    t_client_info *client_info = (t_client_info *)arg;
    int client_socket = client_info->client_socket;
    free(client_info);

    t_packet request = receive_packet(client_socket);
    
    if (request.type != PACKET_TYPE_UINT8) {
        fprintf(stderr, "Failed to receive packet from client\n");
        close(client_socket);
        pthread_exit(NULL);
    }

    switch(request.u_payload.uint8_data) {
        case AUTH_LOGIN:
            handle_login(client_socket);
            break;
        case AUTH_SIGN_UP:
            handle_sign_up(client_socket);
            break;
        default:
            fprintf(stderr, "wrong action from client\n");
            break;
    }
    close(client_socket);
    pthread_exit(NULL);
}

