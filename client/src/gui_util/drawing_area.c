#include "gui_util.h"

GtkDrawingArea *create_drawing_area(
        int width,
        int height,
        gboolean (*callback_function)(GtkWidget *, cairo_t *, gpointer *),
        gpointer *user_data) {
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, width, height);
    g_signal_connect(
            G_OBJECT(drawing_area),
            "draw",
            G_CALLBACK(callback_function),
            user_data
    );
    return GTK_DRAWING_AREA(drawing_area);
}
