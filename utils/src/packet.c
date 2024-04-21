#include "packet.h"


t_packet create_packet(t_packet_type type, const void *data) {

    t_packet packet = {0};

    packet.type = type;
    packet.data_size = sizeof(packet.type);
    switch (type) {
        case PACKET_TYPE_STRING:
            packet.u_payload.s_string.length = strlen((const char *)data);
            packet.u_payload.s_string.data = malloc(packet.u_payload.s_string.length + 1);
            if (!packet.u_payload.s_string.data) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(packet.u_payload.s_string.data, (const char *)data);
            packet.data_size += sizeof(packet.u_payload.s_string.length)
                        + packet.u_payload.s_string.length;
            break;
        case PACKET_TYPE_CHAT:
            packet.u_payload.chat_data = malloc(sizeof(t_chat));
            if (!packet.u_payload.chat_data) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            memcpy(packet.u_payload.chat_data, data, sizeof(t_chat));
            packet.data_size = sizeof(t_chat);
            break;
        case PACKET_TYPE_UINT8:
            packet.u_payload.uint8_data = *(const uint8_t *)data;
            packet.data_size += sizeof(packet.u_payload.uint8_data);
            break;
        case PACKET_TYPE_UINT16:
            packet.u_payload.uint16_data = htons(*(const uint16_t *)data);
            packet.data_size += sizeof(packet.u_payload.uint16_data);
            break;
        case PACKET_TYPE_UINT32:
            packet.u_payload.uint32_data = htonl(*(const uint32_t *)data);
            packet.data_size += sizeof(packet.u_payload.uint32_data);
            break;
        default:
            fprintf(stderr, "Unknown packet type in create\n");
            exit(EXIT_FAILURE);
    }

    return packet;
}

void send_packet(int socket_fd, t_packet *packet) {
    if (socket_fd < 0) {
        fprintf(stderr, "No connection, unable to send a packet\n");
        return;
    }

    char *buffer = malloc(packet->data_size);
    if (!buffer) {
        perror("malloc");
        return;
    }

    memcpy(buffer, &(packet->type), sizeof(packet->type));
    char* serialized_data = NULL;
    switch (packet->type) {
        case PACKET_TYPE_STRING:
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.s_string.length),
                    sizeof(packet->u_payload.s_string.length));
            memcpy(buffer + sizeof(packet->type) + sizeof(packet->u_payload.s_string.length),
                    packet->u_payload.s_string.data, packet->u_payload.s_string.length);
            break;
        case PACKET_TYPE_CHAT:
            serialized_data = serialize_chat(packet->u_payload.chat_data);
            int data_len = strlen(serialized_data) + 1;
            memcpy(buffer + sizeof(packet->type), &data_len, sizeof(data_len));
            memcpy(buffer + sizeof(packet->type) + sizeof(data_len), serialized_data,
                   strlen(serialized_data));
            break;
        case PACKET_TYPE_UINT8:
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.uint8_data),
                    sizeof(packet->u_payload.uint8_data));
            break;
        case PACKET_TYPE_UINT16:
            packet->u_payload.uint16_data = packet->u_payload.uint16_data;
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.uint16_data),
                    sizeof(packet->u_payload.uint16_data));
            
            break;
        case PACKET_TYPE_UINT32:
            packet->u_payload.uint32_data = packet->u_payload.uint32_data;
            memcpy(buffer + sizeof(packet->type), &(packet->u_payload.uint32_data),
                    sizeof(packet->u_payload.uint32_data));
            break;
        default:
            fprintf(stderr, "Unknown packet typerr\n");
            free(buffer);
            return;
    }

    ssize_t sent_bytes = send(socket_fd, buffer, packet->data_size, 0);
    if (sent_bytes < 0) {
        perror("send");
    } else if (sent_bytes != (ssize_t)packet->data_size) {
        fprintf(stderr, "Failed to send the entire packet\n");
    }

    free(buffer);
}

t_packet receive_packet(int socket_fd) {
    t_packet packet = {0};
    if (socket_fd < 0) {
        fprintf(stderr, "No connection, unable to receive to packet\n");
        return packet;
    }
    ssize_t bytes_received = recv(socket_fd, &(packet.type), sizeof(packet.type), 0);
    if (bytes_received != sizeof(packet.type)) {
        fprintf(stderr, "Failed to receive packet type");
        exit(EXIT_FAILURE);
    }
    char* serialized_data = NULL;
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
        case PACKET_TYPE_CHAT:
            bytes_received = recv(socket_fd, &(packet.data_size), sizeof(packet.data_size), 0);
            if (bytes_received != sizeof(packet.data_size)) {
                fprintf(stderr, "Failed to receive chat data size\n");
                exit(EXIT_FAILURE);
            }
            serialized_data = malloc(packet.data_size);
            if (!serialized_data) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            bytes_received = recv(socket_fd, serialized_data, packet.data_size, 0);
            if (bytes_received != packet.data_size) {
                fprintf(stderr, "Failed to receive chat data\n");
                exit(EXIT_FAILURE);
            }
            packet.u_payload.chat_data = deserialize_chat(serialized_data);
            free(serialized_data);
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
            fprintf(stderr, "Unknown packet type received\n");
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
