#include "socket_operations.h"

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) { 
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const int port) {
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);

    int res = bind(sockfd, (struct sockaddr *) &adr, sizeof(adr));
    if (res == -1) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

void Listen (int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd) {
    int res = accept(sockfd, NULL, NULL);
    if( res == -1) {
        perror("accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    return res;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        mx_printstr("inet_pton failed: src does not contain a character"
                " string represetning a valid network addres in the specified"
                " address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

int create_and_connect_socket(const char* server_address, int port) {
    int socket = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    Inet_pton(AF_INET, server_address,
              &server_addr.sin_addr); // need to be optimize
    Connect(socket, (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    return socket;
}

