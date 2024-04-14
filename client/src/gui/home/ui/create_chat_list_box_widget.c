#include "home.h"

static void set_chat_list_item_image(GtkBox *root_box,
                                     char *path,
                                     char first_name_letter) {
    GtkWidget *avatar_widget = create_avatar_widget(
            first_name_letter,
            60,
            "chat_list_item_default_avatar",
            path,
            draw_rounded_square_image
    );
    add_widget_to_box(root_box, avatar_widget, false, false, 0);
}

static void set_chat_list_item_name(GtkBox *root_box, char *name) {
    GtkWidget *label = gtk_label_new(name);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_widget_set_name(label, "chat_list_item_name");
    add_widget_to_box(root_box, label, false, false, 0);
}

static void set_chat_list_item_last_message(GtkBox *root_box, Chat *chat) {
    char *last_message_text;
    if (chat->messages != NULL) {
        Message *last_message = get_chat_last_message(chat);
        last_message_text = last_message->text;
    }
    else {
        last_message_text = "Chat is empty";
    }
    GtkWidget *label = gtk_label_new(last_message_text);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_widget_set_name(label, "chat_list_item_last_message");
    add_widget_to_box(root_box, label, false, false, 0);
}

static void set_chat_list_item_unread_messages_indication(GtkBox *root_box,
                                                          int unread_messages_count) {
    if (unread_messages_count == 0) {
        set_class(GTK_WIDGET(root_box), "read_chat_list_item");
    }
    else {
        char *unread_messages_count_str;
        asprintf(&unread_messages_count_str, "%d", unread_messages_count);
        GtkWidget *label = gtk_label_new(unread_messages_count_str);
        gtk_label_set_width_chars(GTK_LABEL(label), 3);
        gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
        gtk_widget_set_name(label, "chat_list_item_unread_messages");
        add_widget_to_box(root_box, label, false, false, 0);
        set_class(GTK_WIDGET(root_box), "unread_chat_list_item");
        free(unread_messages_count_str);
    }
}

GtkWidget *create_chat_list_box_widget(gpointer item,
                                       gpointer user_data) {
    if (user_data == NULL) {}
    Chat *chat = (Chat *)item;
    GtkWidget *root_box_widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    GtkBox *root_box = GTK_BOX(root_box_widget);

    gtk_widget_show(root_box_widget);
    gtk_widget_set_name(root_box_widget, "chat_list_item_root");

    set_chat_list_item_image(root_box, chat->image_path, chat->name[0]);

    GtkBox *name_and_message_box =
            GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 2));
    add_widget_to_box(
            root_box,
            GTK_WIDGET(name_and_message_box),
            true,
            true,
            0
    );
    gtk_widget_set_valign(GTK_WIDGET(name_and_message_box), GTK_ALIGN_CENTER);

    set_chat_list_item_name(name_and_message_box, chat->name);
    set_chat_list_item_last_message(name_and_message_box, chat);
    set_chat_list_item_unread_messages_indication(
            root_box,
            chat->unread_messages_count
    );
    return root_box_widget;
}
