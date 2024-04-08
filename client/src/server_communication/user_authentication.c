#include "user_authentication.h"

t_client_status_code process_user_authentication(char* server_address, int port, char* username, char* password,
                                                 t_client_codes authentication_code) {
	int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NO_CONNECTION_WITH_SERVER;

    t_packet login_request = create_packet(PACKET_TYPE_UINT8, &authentication_code);
    t_packet user = create_packet(PACKET_TYPE_STRING, username);
    t_packet pass = create_packet(PACKET_TYPE_STRING, password);

    send_and_release_packet(client_socket, &login_request);
    send_and_release_packet(client_socket, &user);
    send_and_release_packet(client_socket, &pass);

    t_client_status_code status_code = receive_packet(client_socket).u_payload.uint8_data;

    close(client_socket);

    return status_code;
}

