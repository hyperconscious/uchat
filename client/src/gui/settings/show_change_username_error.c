#include "settings.h"

void show_change_username_error(char *error) {
    GtkLabel *error_label = get_label(CHANGE_USERNAME_ERROR_LABEL_ID);
    gtk_label_set_text(error_label, error);
}
