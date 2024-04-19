#include "user_authentication.h"

char* process_user_authentication(char* server_address, int port, char* username, char* password,
                                                 t_client_rq authentication_code) {
	int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket < 0)
        return strdup("No connection with server");

    t_packet login_request = create_packet(PACKET_TYPE_UINT8, &authentication_code);
    t_packet user = create_packet(PACKET_TYPE_STRING, username);
    t_packet pass = create_packet(PACKET_TYPE_STRING, password);

    send_and_release_packet(client_socket, &login_request);
    send_and_release_packet(client_socket, &user);
    send_and_release_packet(client_socket, &pass);
    t_client_status_code status_code = receive_packet(client_socket).u_payload.uint8_data;
    int id;
    switch (status_code) {
        case WRONG_PASSWORD:
            return strdup("Wrong password");
            break;
        case LOGIN_DOESNT_EXIST:
            return strdup("This login doesn't exist");
            break;
        case LOGIN_ALREADY_EXIST:
            return strdup("This login already exist");
            break;
        case SUCCESS_REGISTRATION:
            id = receive_packet(client_socket).u_payload.uint32_data;
            (void)id;
            return strdup("success");
            break;
        case SUCCESS_LOGIN:
            id = receive_packet(client_socket).u_payload.uint32_data;
            (void)id;
            return strdup("success");
            break;
        default:
            return strdup("Unefined error. Try again later.");
            break;
    }
    close(client_socket);
    return strdup("Unefined error. Try again later.");
}

