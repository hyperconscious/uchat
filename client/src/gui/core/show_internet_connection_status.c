#include "core.h"

void show_internet_connection_status(t_connection_code available) {
    GtkWidget *indicator_widget = get_widget(INTERNET_CONNECTION_INDICATOR_ID);
    char *indicator_widget_name;

    switch (available) {
        case UNAVAIBLE:
            indicator_widget_name = INTERNET_CONNECTION_NOT_AVAILABLE_INDICATOR;
            break;
        case AVAIBLE:
            indicator_widget_name = INTERNET_CONNECTION_AVAILABLE_INDICATOR;
            break;
        default:
            indicator_widget_name = INTERNET_CONNECTION_WAITING_INDICATOR;
    }

    gtk_widget_set_name(indicator_widget, indicator_widget_name);
}
