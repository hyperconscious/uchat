#include "auth.h"

void set_selected_language_button_style(char *id) {
    gtk_widget_set_name(get_widget(ENGLISH_LANGUAGE_BUTTON_ID), "");
    gtk_widget_set_name(get_widget(FRENCH_LANGUAGE_BUTTON_ID), "");
    gtk_widget_set_name(get_widget(SPANISH_LANGUAGE_BUTTON_ID), "");
    gtk_widget_set_name(get_widget(CHINESE_LANGUAGE_BUTTON_ID), "");
    gtk_widget_set_name(get_widget(UKRAINIAN_LANGUAGE_BUTTON_ID), "");
    gtk_widget_set_name(get_widget(GERMAN_LANGUAGE_BUTTON_ID), "");

    gtk_widget_set_name(get_widget(id), "button_secondary_selected");
}
