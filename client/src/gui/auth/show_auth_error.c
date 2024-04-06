#include "auth.h"

void show_auth_error(char *error) {
    GtkLabel *error_label = get_label(AUTH_ERROR_LABEL_ID);
    GtkWidget *error_label_widget = GTK_WIDGET(error_label);

    gtk_label_set_text(error_label, error);
    gtk_widget_show(error_label_widget);
}
