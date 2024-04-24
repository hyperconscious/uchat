#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct chat_s{
    long id;
    long owner_id;
    char *name;
    char *creation_time;
    bool is_private;
} t_db_chat;

typedef struct {
    uint32_t id;
    char *name;
    char *image_url;
} Person;

typedef struct 
{
    uint32_t id;
    char *text;
    uint32_t user_id;
    uint32_t chat_id;
    bool is_readed;
    char *time;
} t_db_message;
