#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include "string_utils.h"

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, int port);
void Listen (int sockfd, int backlog);
int Accept(int sockfd);
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *src, void *dst);

