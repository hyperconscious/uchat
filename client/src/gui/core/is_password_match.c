#include "core.h"

bool is_password_match(char *password1,
                       char *password2) {
    return strcmp(password1, password2) == 0;
}
