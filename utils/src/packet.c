#include "packet.h"

t_packet create_packet(t_packet_type type, const void *data) {
    t_packet packet;
    packet.type = type;
    switch (type) {
        case PACKET_TYPE_STRING:
            packet.u_payload.s_string.length = strlen((const char *)data);
            packet.u_payload.s_string.data = malloc(packet.u_payload.s_string.length + 1);
            strcpy(packet.u_payload.s_string.data, (const char *)data);
            break;
        case PACKET_TYPE_UINT8:
            packet.u_payload.uint8_data = *(const uint8_t *)data;
            break;
        case PACKET_TYPE_UINT16:
            packet.u_payload.uint16_data = htons(*(const uint16_t *)data);
            break;
        case PACKET_TYPE_UINT32:
            packet.u_payload.uint32_data = htonl(*(const uint32_t *)data);
            break;
        default:
            fprintf(stderr, "Unknown packet type\n");
            exit(EXIT_FAILURE);
    }

    return packet;
}

void send_packet(int socket_fd, t_packet *packet) {
    if (socket_fd < 0) {
        fprintf(stderr, "No connection, unable to send a packet\n");
        return;
    }
    size_t data_size = sizeof(packet->type);
    switch (packet->type) {
        case PACKET_TYPE_STRING:
            data_size += sizeof(packet->u_payload.s_string.length)
                        + packet->u_payload.s_string.length;
            break;
        case PACKET_TYPE_UINT8:
            data_size = sizeof(packet->type) + sizeof(packet->u_payload.uint8_data);
            break;
        case PACKET_TYPE_UINT16:
            data_size += sizeof(packet->u_payload.uint16_data);
            break;
        case PACKET_TYPE_UINT32:
            data_size += sizeof(packet->u_payload.uint32_data);
            break;
        default:
            fprintf(stderr, "Unknown packet type\n");
            return;
    }

    char *buffer = malloc(data_size);
    if (!buffer) {
        perror("malloc");
        return;
    }

    memcpy(buffer, &(packet->type), sizeof(packet->type));

    switch (packet->type) {
        case PACKET_TYPE_STRING:
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.s_string.length),
                    sizeof(packet->u_payload.s_string.length));
            memcpy(buffer + sizeof(packet->type) + sizeof(packet->u_payload.s_string.length),
                    packet->u_payload.s_string.data, packet->u_payload.s_string.length);
            break;
        case PACKET_TYPE_UINT8:
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.uint8_data),
                    sizeof(packet->u_payload.uint8_data));
            break;
        case PACKET_TYPE_UINT16:
            packet->u_payload.uint16_data = htons(packet->u_payload.uint16_data);
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.uint16_data),
                    sizeof(packet->u_payload.uint16_data));
            break;
        case PACKET_TYPE_UINT32:
            packet->u_payload.uint32_data = htonl(packet->u_payload.uint32_data);
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.uint32_data),
                    sizeof(packet->u_payload.uint32_data));
            break;
        default:
            fprintf(stderr, "Unknown packet type\n");
            free(buffer);
            return;
    }

    ssize_t sent_bytes = send(socket_fd, buffer, data_size, 0);
    if (sent_bytes < 0) {
        perror("send");
    } else if (sent_bytes != (ssize_t)data_size) {
        fprintf(stderr, "Failed to send the entire packet\n");
    }

    free(buffer);
}

t_packet receive_packet(int socket_fd) {
    t_packet packet;
    if (socket_fd < 0) {
        fprintf(stderr, "No connection, unable to send a packet\n");
        return packet;
    }
    
    ssize_t bytes_received = recv(socket_fd, &(packet.type), sizeof(packet.type), 0);
    if (bytes_received != sizeof(packet.type)) {
        fprintf(stderr, "Failed to receive packet type\n");
        exit(EXIT_FAILURE);
    }

    switch (packet.type) {
        case PACKET_TYPE_STRING:
            bytes_received = recv(socket_fd, &(packet.u_payload.s_string.length),
                                    sizeof(packet.u_payload.s_string.length), 0);
            if (bytes_received != sizeof(packet.u_payload.s_string.length)) {
                fprintf(stderr, "Failed to receive string length\n");
                exit(EXIT_FAILURE);
            }
            packet.u_payload.s_string.data = malloc(packet.u_payload.s_string.length + 1);
            bytes_received = recv(socket_fd, packet.u_payload.s_string.data,
                                    packet.u_payload.s_string.length, 0);
            if (bytes_received != (ssize_t)packet.u_payload.s_string.length) {
                fprintf(stderr, "Failed to receive string data\n");
                exit(EXIT_FAILURE);
            }
            packet.u_payload.s_string.data[packet.u_payload.s_string.length] = '\0';
            break;
        case PACKET_TYPE_UINT8:
            bytes_received = recv(socket_fd, &(packet.u_payload.uint8_data),
                                    sizeof(packet.u_payload.uint8_data), 0);
            if (bytes_received != sizeof(packet.u_payload.uint8_data)) {
                fprintf(stderr, "Failed to receive uint8 data\n");
                exit(EXIT_FAILURE);
            }
            break;
        case PACKET_TYPE_UINT16:
            bytes_received = recv(socket_fd, &(packet.u_payload.uint16_data),
                                    sizeof(packet.u_payload.uint16_data), 0);
            if (bytes_received != sizeof(packet.u_payload.uint16_data)) {
                fprintf(stderr, "Failed to receive uint16 data\n");
                exit(EXIT_FAILURE);
            }
            packet.u_payload.uint16_data = ntohs(packet.u_payload.uint16_data);
            break;
        case PACKET_TYPE_UINT32:
            bytes_received = recv(socket_fd, &(packet.u_payload.uint32_data),
                                    sizeof(packet.u_payload.uint32_data), 0);
            if (bytes_received != sizeof(packet.u_payload.uint32_data)) {
                fprintf(stderr, "Failed to receive uint32 data\n");
                exit(EXIT_FAILURE);
            }
            packet.u_payload.uint32_data = ntohl(packet.u_payload.uint32_data);
            break;
        default:
            fprintf(stderr, "Unknown packet type\n");
            exit(EXIT_FAILURE);
    }
    
    return packet;
}

void free_packet(t_packet *packet) {
    if (packet->type == PACKET_TYPE_STRING) {
        free(packet->u_payload.s_string.data);
    }
}

void send_and_release_packet(int socket_fd, t_packet *packet) {
    send_packet(socket_fd, packet);
    free_packet(packet);
}
