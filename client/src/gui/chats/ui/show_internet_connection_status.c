#include "home.h"

void show_internet_connection_status(bool available) {
    GtkWidget *indicator_widget = get_widget(INTERNET_CONNECTION_INDICATOR_ID);
    char *indicator_widget_name = available
                                  ? "internet_connection_available_indicator"
                                  : "internet_connection_not_available_indicator";
    gtk_widget_set_name(indicator_widget, indicator_widget_name);
}
