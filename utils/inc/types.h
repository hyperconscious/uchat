#pragma once

typedef struct chat_s{
    long id;
    long owner_id;
    char *name;
    char *creation_time;
} t_db_chat;

typedef struct {
    long id;
    char *name;
    char *image_url;
} Person;

typedef struct 
{
    uint32_t id;
    char *text;
    uint32_t user_id;
    bool is_readed;
    char *time;
    int32_t chat_id;
} t_db_message;
