#include "home.h"

void set_chat_image(GtkBox *root_box, char *image_path) {
    GtkImage *image = image_new(image_path);
    add_widget_to_box(root_box, GTK_WIDGET(image), 0);
}

void set_chat_name(GtkBox *root_box, char *name) {
    GtkWidget *label = gtk_label_new(name);
    add_widget_to_box(root_box, label, 0);
}

void set_chat_last_message(GtkBox *root_box, char *last_message) {
    GtkWidget *label = gtk_label_new(last_message);
    add_widget_to_box(root_box, label, 0);
}

void set_chat_unread_messages(GtkBox *root_box,
                              int unread_messages_count) {
    char unread_message_count_str[20];
    sprintf(unread_message_count_str, "%d", unread_messages_count);

    GtkWidget *label = gtk_label_new(unread_message_count_str);
    add_widget_to_box(root_box, label, 0);
}

void set_chat_read_style(GtkBox *root_box,
                         GtkListBoxRow *new_item,
                         int unread_message_count) {
    char *class;

    if (unread_message_count == 0) {
        class = "read_chat_list_item";
    }
    else {
        set_chat_unread_messages(root_box, unread_message_count);
        class = "unread_chat_list_item";
    }

    set_class(GTK_WIDGET(new_item), class);
}

void create_new_chat_list_item(Chat chat) {
    GtkWidget *root_box_widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    GtkBox *root_box = GTK_BOX(root_box_widget);

    gtk_widget_show(root_box_widget);
    GtkListBoxRow *new_item = list_box_append(CHAT_LIST_ID, root_box_widget);

    set_chat_image(root_box, chat.image_path);

    GtkBox *name_and_message_box = GTK_BOX(
            gtk_box_new(GTK_ORIENTATION_VERTICAL, 2));
    add_widget_to_box(root_box, GTK_WIDGET(name_and_message_box), 0);

    set_chat_name(name_and_message_box, chat.name);
    set_chat_last_message(name_and_message_box, chat.last_message);

    set_chat_read_style(root_box, new_item, chat.unread_message_count);
}
