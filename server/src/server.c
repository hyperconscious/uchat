#include "server.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		return 1;
	}
    // db processing...

    int server_socket = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(server_socket, atoi(argv[1]));
    Listen(server_socket, MAX_CLIENTS);
    while(1) {
        int client_socket = Accept(server_socket);
        
        t_client_info *client_info = malloc(sizeof(t_client_info));
        client_info->client_socket = client_socket;

        create_thread(handle_client, (void *)client_info);
    }
    
    close(server_socket);
    return 0;
}

