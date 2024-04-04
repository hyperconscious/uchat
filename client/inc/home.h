#pragma once

#include "gui_util.h"

#define HOME_WINDOW_ID "home_window"
#define CHAT_LIST_ID "chat_list"

typedef struct {
    char *image_path;
    char *name;
    char *last_message;
    int unread_message_count;
} Chat;

void set_selected_chat_style(void);

void create_new_chat_list_item(Chat chat);
