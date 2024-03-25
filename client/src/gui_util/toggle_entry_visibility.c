#include "gui_util.h"

void toggle_entry_visibility(char *id) {
    GtkEntry *entry = get_entry(id);
    bool is_visible = gtk_entry_get_visibility(entry);
    char *new_icon_path = is_visible ? IC_SHOW_PATH : IC_HIDE_PATH;

    set_entry_icon_secondary(id, new_icon_path);
    gtk_entry_set_visibility(entry, !is_visible);
}
