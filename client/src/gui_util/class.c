#include "gui_util.h"

void set_class(GtkWidget *widget,
               char *class) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, class);
}

void update_class(GtkWidget *widget,
                  char *old_class,
                  char *new_class) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_remove_class(context, old_class);
    gtk_style_context_add_class(context, new_class);
}
