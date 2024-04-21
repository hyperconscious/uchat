#include "home.h"

GListStore *all_chats_list_store = NULL;
GListStore *visible_chats_list_store = NULL;

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

static void delete_searched_chats() {
    int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));

    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
        if (chat && chat->searching && chat->messages == NULL)
            remove_chat(chat, all_chats_list_store);
    }
 /*   size = g_list_model_get_n_items(G_LIST_MODEL(visible_chats_list_store));

    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(visible_chats_list_store, i);
        if (chat && chat->searching && chat->messages == NULL)
            remove_chat(chat, visible_chats_list_store);
    }*/
}

static void create_searching_chat(char* name) {
    int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));
    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
        if (chat && (strcmp(chat->name, name) == 0)) {
            return;
        }
    }
    Chat* chat = create_chat(0, NULL, name, NULL, 0, true, 
                                get_current_time_millis());
    add_chat_sorted_to_all_list_store(chat);
}

static void show_chats_am_in(){
    int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));

    for (int i = 0; i < size; i++) {
        Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
        if (chat) {
            add_chat_sorted_to_visible_list_store(chat);
        }
    }
    
}

void on_search_message_entry_changed(void) {
    if(strlen(get_entry_text(SEARCH_CHAT_ENTRY_ID)) == 0){
        delete_searched_chats();
        show_chats_am_in();
        return;
    }

    uint16_t count = 0;
    char **founded_chats = rq_search_chats(get_entry_text(SEARCH_CHAT_ENTRY_ID),
                            &count, serverAddress, Port);
    for (uint16_t i = 0; i < count; i++) {
        create_searching_chat(founded_chats[i]);
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
