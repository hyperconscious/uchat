#include "home.h"

static void set_chat_image(char *path,
                           char first_name_letter) {
    GtkWidget *avatar_widget = create_avatar_widget(
            first_name_letter,
            50,
            "circle_default_avatar",
            path,
            false,
            draw_circle_image
    );

    GtkBox *chat_header_box = get_box(CHAT_HEADER_BOX_ID);
    add_widget_to_box(chat_header_box, avatar_widget, false, false, 0);
    gtk_box_reorder_child(chat_header_box, avatar_widget, 0);
}

static void set_chat_name(char *name) {
    GtkLabel *chat_name_label = get_label(CHAT_NAME_LABEL_ID);
    gtk_label_set_text(chat_name_label, name);
}

static void set_chat_messages(t_list *messages) {
    clear_list_box(CHAT_MESSAGES_LIST_ID);

    if (messages == NULL)
        return;

    int messages_count = mx_list_size(messages);
    Message *previous_message = NULL;

    for (int i = 0; i < messages_count; i++) {
        Message *message = mx_get_element_by_index(messages, i);
        if (message != NULL) {
            add_messages_list_box_row(message, previous_message);
            previous_message = message;
        }
    }
}

static void show_chat_box(void) {
    if (get_widget_visible(CHAT_BOX_ID) == false) {
        gtk_widget_destroy(get_widget(CHAT_NOT_SELECTED_BOX_ID));
        GtkBox *chats_content_box = get_box(CHATS_BOX_ID);
        GtkWidget *chat_box = get_widget(CHAT_BOX_ID);
        add_widget_to_box(chats_content_box, chat_box, true, true, 0);
    }
}

static void unselect_previous_selected_chat(
        guint previous_selected_chat_index) {
    Chat *previous_selected_chat = get_list_store_item_by_index(
            all_chats_list_store,
            previous_selected_chat_index
    );
    previous_selected_chat->selected = false;

    GtkContainer *chat_header_box = GTK_CONTAINER(get_box(CHAT_HEADER_BOX_ID));
    GtkWidget *previous_avatar = get_container_first_child(chat_header_box);
    gtk_widget_destroy(previous_avatar);
}

static void set_messages_read(GtkListBoxRow *row,
                              Chat *chat) {
    if (chat->unread_messages_count > 0) {
        chat->unread_messages_count = 0;
        int label_index = chat->image_path == NULL ? 1 : 0;
        GtkBox *box = get_box_from_container(GTK_CONTAINER(row), 0);
        GtkLabel *label = get_label_from_container(GTK_CONTAINER(box),
                                                   label_index);
        remove_class(GTK_WIDGET(box), "unread_chat_list_item");
        set_class(GTK_WIDGET(box), "read_chat_list_item");
        gtk_widget_destroy(GTK_WIDGET(label));
    }
}

void select_chat(GtkListBoxRow *selected_row) {
    int selected_chat_index = gtk_list_box_row_get_index(selected_row);
    Chat *selected_chat = get_list_store_item_by_index(
            visible_chats_list_store,
            selected_chat_index
    );

    guint previous_selected_chat_index;
    bool is_chat_selected =
            get_selected_chat_index(&previous_selected_chat_index);

    if (!is_chat_selected || !selected_chat->selected) {
        if (is_chat_selected)
            unselect_previous_selected_chat(previous_selected_chat_index);

        selected_chat->selected = true;
        set_chat_name(selected_chat->name);
        set_chat_image(selected_chat->image_path, selected_chat->name[0]);
        set_chat_messages(selected_chat->messages);
        set_messages_read(selected_row, selected_chat);
        set_chat_list_box_row_selected_style(selected_row);
        show_chat_box();

        g_timeout_add(50, scroll_window_to_bottom,
                      CHAT_MESSAGES_SCROLLED_WINDOW_ID);
    }
}
