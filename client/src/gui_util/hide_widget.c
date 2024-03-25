#include "gui_util.h"

void hide_widget(char *id) {
    GtkWidget *widget = get_widget(id);
    gtk_widget_hide(widget);
}
