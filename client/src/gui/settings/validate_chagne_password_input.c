#include "settings.h"

bool validate_change_password_input(char *new_password,
                                    char *confirm_new_password,
                                    char *old_password,
                                    char *entered_old_password) {
    if (!is_password_match(old_password, entered_old_password)) {
        show_change_password_error("Your old password is not correct.\n"
                                   "Please, try again");
        return false;
    }
    else if (!is_password_valid(new_password)) {
        show_change_password_error(
                "The password must have at least:\n"
                "- 6 characters in length\n"
                "- 1 Latin letter\n"
                "- 1 digit"
        );
        return false;
    }
    else if (!is_password_match(new_password, confirm_new_password)) {
        show_change_password_error(
                "Your passwords are not the same.\n"
                "Please enter matching passwords"
        );
        return false;
    }
    else if (is_password_match(old_password, new_password)) {
        show_change_password_error("New password is the same as the old one");
        return false;
    }
    else {
        set_entry_text(OLD_PASSWORD_ENTRY_ID, "");
        set_entry_text(NEW_PASSWORD_ENTRY_ID, "");
        set_entry_text(CONFIRM_NEW_PASSWORD_ENTRY_ID, "");
        return true;
    }
}
