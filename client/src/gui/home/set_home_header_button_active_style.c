#include "home.h"

void set_home_header_button_active_style(char *id) {
    remove_class(get_widget(CHATS_BUTTON_ID), "home_header_button_selected");
    remove_class(get_widget(DISCOVER_BUTTON_ID), "home_header_button_selected");
    remove_class(get_widget(SETTINGS_BUTTON_ID), "home_header_button_selected");

    set_class(get_widget(id), "home_header_button_selected");
}
