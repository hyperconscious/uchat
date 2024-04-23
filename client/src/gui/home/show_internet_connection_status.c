#include "home.h"

void show_internet_connection_status(int available) {
    GtkWidget *indicator_widget = get_widget(INTERNET_CONNECTION_INDICATOR_ID);
    char *indicator_widget_name;

    switch (available) {
        case -1:
            indicator_widget_name = "internet_connection_not_available_indicator";
            break;
        case 1:
            indicator_widget_name = "internet_connection_available_indicator";
            break;
        default:
            indicator_widget_name = "internet_connection_waiting_indicator";
    }

    gtk_widget_set_name(indicator_widget, indicator_widget_name);
}
