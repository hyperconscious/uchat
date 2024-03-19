#include "gui_util.h"

void set_entry_icon_secondary(char *id,
                              char *icon_file_path) {
    GtkEntry *entry = get_entry(id);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(icon_file_path, NULL);

    gtk_entry_set_icon_from_pixbuf(entry, GTK_ENTRY_ICON_SECONDARY, pixbuf);
}
