#include "handle_client.h"

void *handle_client(void *arg) {
    t_client_info *client_info = (t_client_info *)arg;
    int client_socket = client_info->client_socket;
    free(client_info);

	t_client_codes request;
	recv(client_socket, &request, sizeof(request), 0);

	switch(request) {
		case AUTH_LOGIN:
			mx_printstr("login");
			//function call;
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

