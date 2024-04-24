#pragma once

#define _GNU_SOURCE
#include "gui_util.h"
#include <stdio.h>
#include "core.h"
#include "requests.h"
#include "string_utils.h"

#define CHANGE_AVATAR_BOX_ID "change_avatar_box"
#define AVATAR_FILE_CHOOSER_BUTTON "avatar_file_chooser_button"
#define CHANGE_USERNAME_ENTRY_ID "change_username_entry"
#define OLD_PASSWORD_ENTRY_ID "old_password_entry"
#define NEW_PASSWORD_ENTRY_ID "new_password_entry"
#define CONFIRM_NEW_PASSWORD_ENTRY_ID "confirm_new_password_entry"
#define CHANGE_USERNAME_ERROR_LABEL_ID "change_username_error_label"
#define CHANGE_PASSWORD_ERROR_LABEL_ID "change_password_error_label"
#define SETTINGS_CURRENT_USERNAME_LABEL_ID "settings_current_username_label"

extern int Port;
extern char *serverAddress;
extern Person *Client;

void show_change_username_error(char *error);

void show_change_password_error(char *error);

bool validate_change_username_input(char *username);

bool validate_change_password_input(char *new_password,
                                    char *confirm_new_password,
                                    char *old_password,
                                    char *entered_old_password);

void set_chosen_avatar(char user_name_first_letter,
                       char *image_path,
                       bool is_first_set);

void set_current_username(char *username);
