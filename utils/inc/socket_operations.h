#pragma once

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <poll.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "string_utils.h"

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, int port);
void Listen (int sockfd, int backlog);
int Accept(int sockfd);
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *src, void *dst);
int connect_with_timeout(int sockfd, const struct sockaddr *addr, socklen_t
        addrlen, unsigned int timeout_ms);
int create_and_connect_socket(const char* server_address, int port);
