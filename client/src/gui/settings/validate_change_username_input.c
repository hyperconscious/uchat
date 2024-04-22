#include "settings.h"

bool validate_change_username_input(char *username) {
    if (!is_username_valid(username)) {
        show_change_username_error("Username must have 3 characters at least");
        return false;
    }
    else {
       
        return true;
    }
}
