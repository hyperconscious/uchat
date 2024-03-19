#include "server.h"

int main(void) {

    // db processing...

    int server_socket = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(server_socket, PORT);
    Listen(server_socket, MAX_CLIENTS);

    while(1) {
        int client_socket = Accept(server_socket);
        
        // block with client_info; need only socket;
        char login[50];
        read(client_socket, login, sizeof(login));

        t_client_info *client_info = malloc(sizeof(t_client_info));
        client_info->client_socket = client_socket;
        mx_strcpy(client_info->login, login);
        //-----------------------------------------

        create_thread(handle_client, (void *)client_info);
    }
    
    close(server_socket);
    return 0;
}

