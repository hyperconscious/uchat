#include "settings.h"

void set_current_username(char *username) {
    GtkLabel *current_username_label =
            get_label(SETTINGS_CURRENT_USERNAME_LABEL_ID);
    char *current_username_string;
    asprintf(&current_username_string, "Username (The current one is \"%s\")",
             username);
    gtk_label_set_text(current_username_label, current_username_string);
    mx_strdel(&current_username_string);
}
