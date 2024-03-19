#include "client.h"

char* get_login();

int main() {

    // gtk_init();

    // other actions need to be handled by gtk_main

    int client_socket = Socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    Inet_pton(AF_INET, SERVER_ADDR,
                &server_address.sin_addr); // need to be optimized

    Connect(client_socket, (struct sockaddr *)&server_address,
            sizeof(server_address));

    char* login = get_login();
    write(client_socket, login, mx_strlen(login) + 1);

    char message[256];
    while (1) {
        mx_printstr(login); mx_printstr(": ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0; 
        write(client_socket, message, mx_strlen(message) + 1);

        ssize_t nread = read(client_socket, message, sizeof(message));
        if (nread == -1) {
        	mx_strdel(&login);
			perror("read failed");
            exit(EXIT_FAILURE);
        }
        if (nread == 0) {
            mx_strdel(&login);
            mx_printstr("Server connection was closed.\n");
            break;
        }
        mx_printstr("Server: "); mx_printstr(message); mx_printstr("\n");
    }

    mx_strdel(&login);
    close(client_socket);
    return 0;
}

char* get_login() {
    char* login = mx_strnew(20);
    mx_printstr("Enter your login: ");
    fgets(login, sizeof(login), stdin);
    login[strcspn(login, "\n")] = 0;
    return login;
}


