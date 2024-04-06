#include "home.h"
#include "string_utils.h"

GtkWidget *create_avatar_widget(
        char letter,
        int size,
        char *widget_name,
        char *path,
        gboolean (*callback_function)(GtkWidget *, cairo_t *, gpointer *)) {
    GtkWidget *avatar_widget;

    if (path != NULL) {
        avatar_widget = GTK_WIDGET(
                create_drawing_area(
                        size,
                        size,
                        callback_function,
                        (gpointer)path
                )
        );
    }
    else {
        char *letter_as_string = mx_strnew(1);
        letter_as_string[0] = letter;
        GtkWidget *default_avatar_widget = gtk_label_new(letter_as_string);
        gtk_widget_set_size_request(default_avatar_widget, size, size);
        gtk_widget_set_name(default_avatar_widget, widget_name);
        set_class(default_avatar_widget, "default_avatar");
        mx_strdel(&letter_as_string);
        avatar_widget = default_avatar_widget;
    }

    return avatar_widget;
}
