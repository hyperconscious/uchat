#pragma once

#define _GNU_SOURCE

#include "gui_util.h"
#include "list.h"
#include "requests.h"
#include "local_time.h"
#include "core.h"
#include "types.h"

#define HOME_WINDOW_CONTENT_BOX_ID "home_window_content_box"
#define CHATS_BUTTON_ID "chats_button"
#define DISCOVER_BUTTON_ID "discover_button"
#define SETTINGS_BUTTON_ID "settings_button"
#define LOG_OUT_BUTTON_ID "log_out_button"
#define CHATS_BOX_ID "chats_box"
#define CHAT_LIST_BOX_ID "personal_chat_list"
#define SEARCH_CHAT_ENTRY_ID "search_chat_entry"
#define CHAT_NOT_SELECTED_BOX_ID "chat_not_selected_box"
#define CHAT_BOX_ID "chat_box"
#define CHAT_MESSAGES_SCROLLED_WINDOW_ID "chat_messages_scrolled_window"
#define CHAT_HEADER_BOX_ID "chat_header_box"
#define CHAT_HEADER_NAME_AND_AVATAR_BOX_ID "chat_header_name_and_avatar_box"
#define CHAT_IMAGE_ID "chat_image"
#define CHAT_NAME_LABEL_ID "chat_name_label"
#define CHAT_MESSAGES_LIST_ID "chat_messages_list"
#define CHAT_MESSAGE_ENTRY_ID "message_entry"
#define SEND_MESSAGE_BUTTON_ID "send_message_button"
#define LABEL_NO_INTERNET_CONNECTION_ID "label_no_internet_connection"
#define CHAT_ACTIONS_BOX_ID "chat_actions_box"
#define CHAT_ACTIONS_HEADER_BOX_ID "chat_actions_header_box"
#define CHATS_CATEGORY_NOTEBOOK_ID "chats_category_notebook"
#define CREATE_GROUP_CHAT_BUTTON_ID "create_group_chat_button"
#define CHAT_MEMBERS_LIST_ID "chat_members_list"
#define ADD_GROUP_CHAT_MEMBERS_DIALOG_LABEL_ID "add_group_chat_members_dialog_label"
#define ADD_GROUP_CHAT_MEMBERS_DIALOG_SEARCH_ENTRY_ID "add_group_chat_members_dialog_search_entry"
#define ADD_GROUP_CHAT_MEMBERS_DIALOG_ID "add_group_chat_members_dialog"
#define ADD_GROUP_CHAT_MEMBERS_DIALOG_SCROLLED_WINDOW "add_group_chat_members_dialog_scrolled_window"
#define SETTINGS_BOX_ID "settings_box"
#define DISCOVER_BOX_ID "discover_box"

extern int Port;
extern char *serverAddress;
extern Person *Client;
extern GListStore *all_chats_list_store;
extern GListStore *visible_chats_list_store;

typedef struct {
    bool mine;
    uint32_t id;
    long long time_in_millis;
    char *text;
} Message;

struct _Chat {
    GtkWidget parent_instance;
    uint32_t id;
    char *image_path;
    char *name;
    t_list *messages;
    int unread_messages_count;
    bool selected;
    bool searching;
    bool is_private;
    long long creation_time_in_millis;
};

GtkWidget *create_chat_list_box_widget(gpointer item,
                                       gpointer user_data);

void set_home_header_button_active_style(char *id);

t_list *get_chats(void);

void select_chat(GtkListBoxRow *selected_row);

void filter_chats(void);

int get_chat_index_by_id(long id);

guint add_chat_sorted_to_all_list_store(struct _Chat *chat);

void add_chat_sorted(struct _Chat *chat);

guint add_chat_sorted_to_visible_list_store(struct _Chat *chat);

void show_chats_i_am_in(void);

void create_searching_chat(t_db_chat *chat);

void delete_searched_chats(void);

void remove_chat(struct _Chat *chat, GListStore *list);

void add_messages_list_box_row(Message *message,
                               Message *previous_message);

void add_message(struct _Chat *chat,
                 Message *message);

void add_message_to_selected_chat(void);

void show_chats(t_list *chats);

void connect_chat_list_box_row_activated_signal(void);

gboolean get_selected_chat_index(guint *index);

struct _Chat *get_selected_chat(void);

void on_chat_list_item_activated(GtkListBox *listbox,
                                 GtkListBoxRow *row,
                                 gpointer user_data);

void set_chat_list_box_row_selected_style(GtkListBoxRow *selected_row);

struct _Chat *create_chat(long id,
                          char *image_path,
                          const char *name,
                          t_list *messages,
                          int unread_messages_count,
                          bool searching,
                          bool is_private,
                          long long creation_time_in_millis);

Message *create_message(const char *text,
                        bool mine,
                        long long time);

Message *get_chat_last_message(struct _Chat *chat);

void set_chat_list_box_row_selected_style(GtkListBoxRow *selected_row);

void show_chat_actions_box(void);

G_BEGIN_DECLS
#define CHAT_TYPE chat_get_type()
G_DECLARE_FINAL_TYPE(Chat, chat, CHAT, OBJECT, GObject)

G_END_DECLS
