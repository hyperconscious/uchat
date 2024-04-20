#include "gui_util.h"

GtkEntry *get_entry(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_ENTRY(g_object);
}

char *get_entry_text(char *id) {
    GtkEntry *entry = get_entry(id);
    return (char *)gtk_entry_get_text(entry);
}

void set_entry_text(char *id,
                    char *text) {
    GtkEntry *entry = get_entry(id);
    gtk_entry_set_text(entry, text);
}

void toggle_entry_visibility(char *id) {
    GtkEntry *entry = get_entry(id);
    bool is_visible = gtk_entry_get_visibility(entry);
    char *new_icon_path = is_visible ? IC_SHOW_PATH : IC_HIDE_PATH;

    set_entry_icon_secondary(id, new_icon_path);
    gtk_entry_set_visibility(entry, !is_visible);
}

void set_entry_icon_secondary(char *id,
                              char *icon_file_path) {
    GtkEntry *entry = get_entry(id);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(icon_file_path, NULL);

    gtk_entry_set_icon_from_pixbuf(entry, GTK_ENTRY_ICON_SECONDARY, pixbuf);
    g_object_unref(pixbuf);
}
