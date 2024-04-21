#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include "list.h"
#include "types.h"
#include "serializer.h"

typedef enum e_packet_type {
    PACKET_TYPE_INVALID,
    PACKET_TYPE_STRING,
    PACKET_TYPE_CHAT,
    PACKET_TYPE_MESSAGE,
    PACKET_TYPE_UINT8,
    PACKET_TYPE_UINT16,
    PACKET_TYPE_UINT32
}            t_packet_type;

typedef struct {
    t_packet_type type;
    int data_size;
    union {
        struct {
            size_t length;
            char* data;
        } s_string;
        t_chat* chat_data;
        uint8_t uint8_data;
        uint16_t uint16_data;
        uint32_t uint32_data;
    } u_payload;
} t_packet;

t_packet create_packet(t_packet_type type, const void *data);
void send_packet(int socket_fd, t_packet *packet);
t_packet receive_packet(int socket_fd);
void free_packet(t_packet *packet);
void send_and_release_packet(int socket_fd, t_packet *packet);

