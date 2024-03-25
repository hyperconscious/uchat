#include "auth.h"

void validate_sign_up_input(char *username,
                            char *password,
                            char *confirm_password) {
    if (!is_username_valid(username))
        show_auth_error("Username must have 3 characters at least");
    else if (!is_password_valid(password))
        show_auth_error(
                "The password must have at least:\n"
                "- 6 characters in length\n"
                "- 1 Latin letter\n"
                "- 1 digit"
        );
    else if (!is_confirm_password_valid(password, confirm_password))
        show_auth_error(
                "Your passwords are not the same.\n"
                "Please enter matching passwords"
        );
    else
        hide_auth_error();
}
