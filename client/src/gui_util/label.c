#include "gui_util.h"

GtkLabel *get_label(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_LABEL(g_object);
}
