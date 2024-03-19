#include "handle_client.h"

void *handle_client(void *arg) {
    t_client_info *client_info = (t_client_info *)arg;
    int client_socket = client_info->client_socket;
    char login[50];
    mx_strcpy(login, client_info->login);
    free(client_info);


    // in message case :
    ssize_t nread;
    char buf[256];

    while ((nread = read(client_socket, buf, 256)) > 0) {
        mx_printstr(login); mx_printstr(" : "); mx_printstr(buf);
        mx_printstr("\n");
        write(client_socket, buf, nread);
    }

    if (nread == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }

    close(client_socket);

    pthread_exit(NULL);
}

