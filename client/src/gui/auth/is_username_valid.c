#include "auth.h"

bool is_username_valid(char *username) {
    return strlen(username) > 2;
}
