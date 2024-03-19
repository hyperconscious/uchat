#include "auth.h"

bool is_confirm_password_valid(char *password,
                               char *confirm_password) {
    return strcmp(password, confirm_password) == 0;
}
