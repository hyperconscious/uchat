#pragma once

#include "gui_util.h"

bool is_username_valid(char *username);

bool is_password_valid(char *password);

bool is_password_match(char *password1,
                       char *password2);

GtkWidget *create_avatar_widget(
        char letter,
        int size,
        char *widget_name,
        char *path,
        bool is_image_local,
        gboolean (*callback_function)(GtkWidget *, cairo_t *, gpointer *));
