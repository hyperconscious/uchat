#include "gui_util.h"

GtkFileChooser *get_file_chooser_button(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_FILE_CHOOSER(g_object);
}

char *get_file_chooser_button_set_file_name(char *id) {
    GtkFileChooser *file_chooser_button = get_file_chooser_button(id);
    return gtk_file_chooser_get_filename(file_chooser_button);
}
