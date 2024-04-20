#include "home.h"

gboolean scroll_window_to_bottom(gpointer user_data) {
    char *id = (char *)user_data;
    GtkWidget *scrolled_window = get_widget(id);
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(
            GTK_SCROLLED_WINDOW(scrolled_window)
    );
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    return FALSE;
}
