#include "settings.h"

bool validate_change_username_input(char *username) {
    if (!is_username_valid(username)) {
        show_change_username_error("Username must have 3 characters at least");
        return false;
    }
    else {
        set_entry_text(CHANGE_USERNAME_ENTRY_ID, "");
        return true;
    }
}
