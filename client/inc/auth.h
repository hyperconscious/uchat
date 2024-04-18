#pragma once

#include "gui_util.h"
#include "user_authentication.h"
#include "core.h"

#define LOG_IN_USERNAME_ENTRY_ID "log_in_username_entry"
#define LOG_IN_PASSWORD_ENTRY_ID "log_in_password_entry"
#define SIGN_UP_USERNAME_ENTRY_ID "sign_up_username_entry"
#define SIGN_UP_PASSWORD_ENTRY_ID "sign_up_password_entry"
#define SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID "sign_up_confirm_password_entry"
#define AUTH_ERROR_LABEL_ID "auth_error_label"
#define HOME_WINDOW_ID "home_window"

extern int Port;
extern char *serverAddress;

bool validate_sign_up_input(char *username,
                            char *password,
                            char *confirm_password);

bool validate_log_in_input(char *username,
                           char *password);

void show_auth_error(char *error);

void hide_auth_error(void);
