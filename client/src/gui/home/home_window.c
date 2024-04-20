#include "home.h"

GListStore *all_chats_list_store = NULL;
GListStore *visible_chats_list_store = NULL;
t_list *chats_on_search = NULL; //temporary

void on_home_window_show(void) {
    set_home_header_button_active_style(CHATS_BUTTON_ID);
    connect_chat_list_box_row_activated_signal();
    t_list *chats = get_chats();
    show_chats(chats);
    add_widget_to_box(get_box(HOME_WINDOW_CONTENT_BOX_ID),
                      get_widget(SETTINGS_BOX_ID), true, true, 0);
    hide_widget(SETTINGS_BOX_ID);
}

void on_chats_button_clicked(void) {
    set_home_header_button_active_style(CHATS_BUTTON_ID);
    hide_widget(SETTINGS_BOX_ID);
    show_widget(CHATS_BOX_ID);
}

void on_discover_button_clicked(void) {
    set_home_header_button_active_style(DISCOVER_BUTTON_ID);
    hide_widget(CHATS_BOX_ID);
    hide_widget(SETTINGS_BOX_ID);
}

void on_settings_button_clicked(void) {
    set_home_header_button_active_style(SETTINGS_BUTTON_ID);
    hide_widget(CHATS_BOX_ID);
    show_widget(SETTINGS_BOX_ID);
}

void on_log_out_button_clicked(void) {
}

void on_search_message_entry_changed(void) {
    if(strlen(get_entry_text(SEARCH_CHAT_ENTRY_ID)) == 0){
        t_list *chats = get_chats();
        show_chats(chats);
        return;
    }

    t_list *curr = chats_on_search;
    while (curr != NULL) {
        if(curr->data != NULL){
            remove_chat((Chat*)curr->data);
        }
        curr = curr->next; 
    }
  //  if(chats_on_search != NULL)
  //      free(chats_on_search);

    uint16_t count = 0;
    char **founded_chats = search_chats(get_entry_text(SEARCH_CHAT_ENTRY_ID),
                            &count, serverAddress, Port);
    for (uint16_t i = 0; i < count; i++) {
        Chat* chat = create_chat(0, NULL,
                                founded_chats[i], NULL, 0,
                                get_current_time_millis());
        mx_push_back(&chats_on_search, chat);
        add_chat_sorted_all_list_store(chat);
    }
    filter_chats();

    for (uint16_t i = 0; i < count; i++) {
        free(founded_chats[i]);
    }
    free(founded_chats);
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
