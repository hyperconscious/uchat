#include "serializer.h"

char *serialize_message(const t_db_message *message) {
    size_t text_length = strlen(message->text);
    size_t time_length = strlen(message->time);
    size_t buffer_size = sizeof(uint32_t) * 4 + sizeof(bool) + text_length + time_length + 2; // Для '\0'

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    sprintf(buffer, "%u|%s|%u|%u|%d|%s", message->id, message->text, message->user_id,
            message->chat_id, message->is_readed, message->time);

    return buffer;
}

t_db_message deserialize_message(const char *buffer) {
    t_db_message message;

    sscanf(buffer, "%u|%m[^|]|%u|%u|%d|%m[^|]", &message.id, &message.text, &message.user_id,
           &message.chat_id, &message.is_readed, &message.time);

    return message;
}

char *serialize_chat(const t_chat *chat) {
    if (!chat || !chat->name) {
        fprintf(stderr, "Error: NULL chat or chat name pointer\n");
        return NULL;
    }

    size_t name_len = strlen(chat->name);
    size_t serialized_size = sizeof(chat->id) + sizeof(chat->owner_id) + name_len + 1;

    char *serialized_data = malloc(serialized_size);
    if (!serialized_data) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memcpy(serialized_data, &chat->id, sizeof(chat->id));
    memcpy(serialized_data + sizeof(chat->id), &chat->owner_id, sizeof(chat->owner_id));
    strcpy(serialized_data + sizeof(chat->id) + sizeof(chat->owner_id), chat->name);

    return serialized_data;
}
t_chat *deserialize_chat(const char *serialized_data) {
    if (!serialized_data) {
        fprintf(stderr, "Error: NULL serialized data pointer\n");
        return NULL;
    }

    t_chat *chat = malloc(sizeof(t_chat));
    if (!chat) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memcpy(&chat->id, serialized_data, sizeof(chat->id));
    memcpy(&chat->owner_id, serialized_data + sizeof(chat->id), sizeof(chat->owner_id));

    size_t name_len = strlen(serialized_data + sizeof(chat->id) + sizeof(chat->owner_id)) + 1; // +1 для '\0'

    chat->name = malloc(name_len);
    if (!chat->name) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }


    return chat;
}
