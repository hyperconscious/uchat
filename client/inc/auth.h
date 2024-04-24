#pragma once

#include "gui_util.h"
#include "requests.h"
#include "core.h"
#include "types.h"
#include "serializer.h"
#include "string.h"

#define LOG_IN_USERNAME_ENTRY_ID "log_in_username_entry"
#define LOG_IN_PASSWORD_ENTRY_ID "log_in_password_entry"
#define SIGN_UP_USERNAME_ENTRY_ID "sign_up_username_entry"
#define SIGN_UP_PASSWORD_ENTRY_ID "sign_up_password_entry"
#define SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID "sign_up_confirm_password_entry"
#define ENGLISH_LANGUAGE_BUTTON_ID "english_language_button"
#define FRENCH_LANGUAGE_BUTTON_ID "french_language_button"
#define SPANISH_LANGUAGE_BUTTON_ID "spanish_language_button"
#define CHINESE_LANGUAGE_BUTTON_ID "chinese_language_button"
#define UKRAINIAN_LANGUAGE_BUTTON_ID "ukrainian_language_button"
#define GERMAN_LANGUAGE_BUTTON_ID "german_language_button"
#define AUTH_ERROR_LABEL_ID "auth_error_label"
#define AUTH_WINDOW_ID "auth_window"
#define HOME_WINDOW_ID "home_window"

extern int Port;
extern char *serverAddress;
extern Person *Client;



bool validate_sign_up_input(char *username,
                            char *password,
                            char *confirm_password);

bool validate_log_in_input(char *username,
                           char *password);

void show_auth_error(char *error);

void hide_auth_error(void);

void set_selected_language_button_style(char *id);
