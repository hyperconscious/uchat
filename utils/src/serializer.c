#include "serializer.h"

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

    // Определение длины имени чата
    size_t name_len = strlen(serialized_data + sizeof(chat->id) + sizeof(chat->owner_id)) + 1; // +1 для '\0'

    // Выделение памяти под имя чата
    chat->name = malloc(name_len);
    if (!chat->name) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Копирование имени чата
    memcpy(chat->name, serialized_data + sizeof(chat->id) + sizeof(chat->owner_id), name_len);

    return chat;
}
/*t_chat *deserialize_chat(const char *serialized_data) {
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

    size_t name_len = strlen(serialized_data + sizeof(chat->id) + sizeof(chat->owner_id));
    chat->name = malloc(name_len + 1);
    if (!chat->name) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strncpy(chat->name, serialized_data + sizeof(chat->id) + sizeof(chat->owner_id), name_len);
    chat->name[name_len] = '\0';

    return chat;
}*/
