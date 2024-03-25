#pragma once

#include "gui_util.h"

#define LOG_IN_USERNAME_ENTRY_ID "log_in_username_entry"
#define LOG_IN_PASSWORD_ENTRY_ID "log_in_password_entry"
#define SIGN_UP_USERNAME_ENTRY_ID "sign_up_username_entry"
#define SIGN_UP_PASSWORD_ENTRY_ID "sign_up_password_entry"
#define SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID "sign_up_confirm_password_entry"
#define AUTH_ERROR_LABEL_ID "auth_error_label"

bool is_username_valid(char *username);

bool is_password_valid(char *password);

bool is_confirm_password_valid(char *password,
                               char *confirm_password);

void validate_sign_up_input(char *username,
                            char *password,
                            char *confirm_password);

void show_auth_error(char *error);

void hide_auth_error(void);
