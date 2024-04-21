#include "home.h"

void connect_chat_list_box_row_activated_signal(void) {
    GtkListBox *list_box = get_list_box(PERSONAL_CHAT_LIST_BOX_ID);
    GCallback callback = G_CALLBACK(on_chat_list_item_activated);
    g_signal_connect(list_box, "row-activated", callback, NULL);
}
