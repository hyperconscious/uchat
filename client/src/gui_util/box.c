#include "gui_util.h"

void add_widget_to_box(GtkBox *box,
                       GtkWidget *widget,
                       int padding) {
    gtk_box_pack_start(box, widget, false, false, padding);
    gtk_widget_show(widget);
}
