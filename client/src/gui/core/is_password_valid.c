#include "core.h"

bool is_password_valid(char *password) {
    bool contains_digit = false;
    bool contains_letter = false;
    size_t password_length = strlen(password);

    for (size_t i = 0; i < password_length; i++) {
        char current_char = password[i];

        if (isdigit(current_char))
            contains_digit = true;

        if (isalpha(current_char))
            contains_letter = true;
    }

    return contains_digit && contains_letter && password_length >= 6;
}
