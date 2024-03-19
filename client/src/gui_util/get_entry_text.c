#include "gui_util.h"

char *get_entry_text(char *id) {
    GtkEntry *entry = get_entry(id);
    return (char *)gtk_entry_get_text(entry);
}
