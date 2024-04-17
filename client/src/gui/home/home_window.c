#include "home.h"

GListStore *all_chats_list_store = NULL;
GListStore *visible_chats_list_store = NULL;

void on_home_window_show(void) {
    set_home_header_button_active_style(CHATS_BUTTON_ID);
    connect_chat_list_box_row_activated_signal();
    t_list *chats = get_chats();
    show_chats(chats);
}

void on_chats_button_clicked(void) {
    set_home_header_button_active_style(CHATS_BUTTON_ID);
    show_widget(CHATS_CONTENT_BOX_ID);
}

void on_discover_button_clicked(void) {
    set_home_header_button_active_style(DISCOVER_BUTTON_ID);
    hide_widget(CHATS_CONTENT_BOX_ID);
}

void on_settings_button_clicked(void) {
    set_home_header_button_active_style(SETTINGS_BUTTON_ID);
    hide_widget(CHATS_CONTENT_BOX_ID);
}

void on_log_out_button_clicked(void) {
}

void on_search_message_entry_changed(void) {
  //  search_chats(get_entry_text(SEARCH_CHAT_ENTRY_ID), serverAddress, Port);
 //   filter_chats();
}

void on_chat_list_item_activated(GtkListBox *listbox,
                                 GtkListBoxRow *row,
                                 gpointer user_data) {
    if (listbox == NULL || user_data == NULL) {}
    select_chat(row);
}


void on_send_message_button_clicked(void) {
    add_message_to_selected_chat();
}
