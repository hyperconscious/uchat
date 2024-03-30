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

    t_packet user, pass;
	switch(request.u_payload.uint8_data) {
		case AUTH_LOGIN:
            user = receive_packet(client_socket);
			pass = receive_packet(client_socket);
            mx_printstr(user.u_payload.s_data.value);
            mx_printstr(pass.u_payload.s_data.value);
            free_packet(&user);
            free_packet(&pass);
			break;
		case AUTH_SIGN_UP:
			mx_printstr("regestration");
			//function call;
			break;
		//other cases;
	}
    close(client_socket);

    pthread_exit(NULL);
}

