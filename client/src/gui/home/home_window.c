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
    add_widget_to_box(get_box(HOME_WINDOW_CONTENT_BOX_ID),
                      get_widget(DISCOVER_BOX_ID), true, true, 0);
    add_widget_to_box(get_box(CHATS_BOX_ID),
                      get_widget(CHAT_ACTIONS_BOX_ID), true, true, 0);
    hide_widget(SETTINGS_BOX_ID);
    hide_widget(DISCOVER_BOX_ID);
    hide_widget(CHAT_ACTIONS_BOX_ID);
}

void on_chats_button_clicked(void) {
    set_home_header_button_active_style(CHATS_BUTTON_ID);
    hide_widget(SETTINGS_BOX_ID);
    hide_widget(DISCOVER_BOX_ID);
    show_widget(CHATS_BOX_ID);
}

void on_discover_button_clicked(void) {
    set_home_header_button_active_style(DISCOVER_BUTTON_ID);
    hide_widget(CHATS_BOX_ID);
    hide_widget(SETTINGS_BOX_ID);
    show_widget(DISCOVER_BOX_ID);

}

void on_settings_button_clicked(void) {
    set_home_header_button_active_style(SETTINGS_BUTTON_ID);
    hide_widget(CHATS_BOX_ID);
    hide_widget(DISCOVER_BOX_ID);
    show_widget(SETTINGS_BOX_ID);
}

void on_log_out_button_clicked(void) {
    //memory freeing
    /*   int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));

      for (int i = 0; i < size; i++) {
          Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
          if (chat && chat->name){
              remove_chat(chat, all_chats_list_store);
              free(chat->name);
          }
      }
      for (int i = 0; i < size; i++) {
          Chat *chat = get_list_store_item_by_index(visible_chats_list_store, i);
          if (chat && chat->name){
              remove_chat(chat, all_chats_list_store);
          }
      }*/
    open_window(AUTH_WINDOW_ID);
    close_window(HOME_WINDOW_ID);
    // close_window(AUTH_WINDOW_ID);
}

void on_search_message_entry_changed(void) {
    if (strlen(get_entry_text(SEARCH_CHAT_ENTRY_ID)) == 0) {
        g_list_store_remove_all(visible_chats_list_store);
        delete_searched_chats();
        show_chats_i_am_in();
        return;
    }

    uint16_t count = 0;
    t_db_chat *founded_chats = rq_search_chats(
            get_entry_text(SEARCH_CHAT_ENTRY_ID),
            &count, serverAddress, Port);
    for (uint16_t i = 0; i < count; i++) {
        create_searching_chat(founded_chats + i);
    }

    filter_chats();

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

void on_chat_actions_button_clicked(void) {
    show_chat_actions_box();

    hide_widget(SETTINGS_BOX_ID);
    hide_widget(CHAT_BOX_ID);
    show_widget(CHAT_ACTIONS_BOX_ID);
}

void on_chat_actions_back_button_clicked(void) {
    hide_widget(CHAT_ACTIONS_BOX_ID);
    show_widget(CHAT_BOX_ID);
}

void on_chat_actions_box_hide(void) {
    GtkBox *chat_actions_header_box = get_box(CHAT_ACTIONS_HEADER_BOX_ID);
    if (GTK_IS_WIDGET(chat_actions_header_box))
        remove_child_from_box(chat_actions_header_box, 1);
}

void on_chats_category_tab_change(void) {
    GtkNotebook *categories_notebook =
            GTK_NOTEBOOK(get_widget(CHATS_CATEGORY_NOTEBOOK_ID));
    int current_page = gtk_notebook_get_current_page(categories_notebook);
    bool create_group_chat_button_visible = current_page == 0;
    gtk_widget_set_visible(get_widget(CREATE_GROUP_CHAT_BUTTON_ID),
                           create_group_chat_button_visible);
}

void on_create_group_chat_button_clicked(void) {
    gtk_widget_show(get_widget(ADD_GROUP_CHAT_MEMBERS_DIALOG_ID));
    gtk_container_add(
            GTK_CONTAINER(get_widget(ADD_GROUP_CHAT_MEMBERS_DIALOG_ID)),
            get_widget("add_group_chat_members_dialog_root_box")
    );
}

void on_close_add_group_chat_members_dialog_button_clicked(void) {
    gtk_widget_hide(get_widget(ADD_GROUP_CHAT_MEMBERS_DIALOG_ID));
    gtk_container_remove(
            GTK_CONTAINER(get_widget(ADD_GROUP_CHAT_MEMBERS_DIALOG_ID)),
            get_widget("add_group_chat_members_dialog_root_box")
    );
}

void on_add_group_chat_members_search_entry_changed(void) {
//    char *username = get_entry_text(
//            ADD_GROUP_CHAT_MEMBERS_DIALOG_SEARCH_ENTRY_ID);
//    if (strlen(username) == 0) {
//        show_widget(ADD_GROUP_CHAT_MEMBERS_DIALOG_LABEL_ID);
//    }
//    else {
//        show_widget(ADD_GROUP_CHAT_MEMBERS_DIALOG_SCROLLED_WINDOW);
//    }
}
