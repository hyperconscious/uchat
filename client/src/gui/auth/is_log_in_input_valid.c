#include "auth.h"

bool is_log_in_input_valid(char *username,
                           char *password) {
    if (!is_username_valid(username)) {
        show_auth_error("Username isn't valid");
        return false;
    }
    else if (!is_password_valid(password)) {
        show_auth_error("Password isn't valid");
        return false;
    }
    else {
        hide_auth_error();
        return true;
    }
}
