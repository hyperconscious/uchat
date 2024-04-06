#include "auth.h"

void hide_auth_error(void) {
    GtkLabel *error_label = get_label(AUTH_ERROR_LABEL_ID);
    GtkWidget *error_label_widget = GTK_WIDGET(error_label);

    gtk_label_set_text(error_label, "");
    gtk_widget_hide(error_label_widget);
}
