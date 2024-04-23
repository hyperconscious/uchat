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
