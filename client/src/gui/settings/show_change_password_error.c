#include "settings.h"

void show_change_password_error(char *error) {
    GtkLabel *error_label = get_label(CHANGE_PASSWORD_ERROR_LABEL_ID);
    gtk_label_set_text(error_label, error);
}
