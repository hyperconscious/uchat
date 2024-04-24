#include "home.h"
#include "string_utils.h"

static void show_selected_chat_avatar(char name_first_letter,
                                      char *path) {
    GtkBox *chat_actions_header_box = get_box(CHAT_ACTIONS_HEADER_BOX_ID);
    GtkWidget *avatar_widget = create_avatar_widget(
            name_first_letter,
            120,
            "circle_default_avatar",
            path,
            false,
            draw_circle_image
    );
    gtk_widget_set_halign(avatar_widget, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_end(avatar_widget, 38);
    add_widget_to_box(chat_actions_header_box, avatar_widget, true, true, 0);
}

static GtkWidget *create_chat_member_widget(char *name,
                                            char *image_url) {
    GtkWidget *member_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *member_avatar = create_avatar_widget(
            name[0],
            50,
            "circle_default_avatar",
            image_url,
            false,
            draw_circle_image
    );
    GtkWidget *member_name_label = gtk_label_new(name);
    GtkWidget *remove_member_button = gtk_button_new();

    gtk_button_set_image(
            GTK_BUTTON(remove_member_button),
            GTK_WIDGET(image_new("client/src/gui/layout/img/ic_remove.svg", -1,
                                 -1))
    );

    gtk_widget_set_halign(remove_member_button, GTK_ALIGN_END);

    gtk_label_set_ellipsize(GTK_LABEL(member_name_label),
                            PANGO_ELLIPSIZE_END);

    add_widget_to_box(GTK_BOX(member_box), member_avatar, false, false, 0);
    add_widget_to_box(GTK_BOX(member_box), member_name_label, false, false,
                      12);
    add_widget_to_box(GTK_BOX(member_box), remove_member_button, true,
                      true, 12);

    return member_box;
}

static void show_chat_members(void) {
    Person person = {.id = 0, .name = "Andriy", .image_url = NULL};

    for (int i = 0; i < 5; i++) {
        GtkWidget *chat_member_widget =
                create_chat_member_widget(person.name, person.image_url);
        GtkWidget *chat_members_list_separator =
                gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

        gtk_widget_show(chat_member_widget);
        gtk_widget_show(chat_members_list_separator);

        list_box_append(CHAT_MEMBERS_LIST_ID, chat_member_widget);
        list_box_append(CHAT_MEMBERS_LIST_ID, chat_members_list_separator);
    }
}

static void show_selected_chat_name(char *name) {
    GtkLabel *chat_name_label = get_label("chat_actions_chat_name_label");
    gtk_label_set_text(chat_name_label, name);
}

static void show_selected_chat_member_count(int member_count) {
    GtkLabel *member_count_label =
            get_label("chat_actions_chat_member_count_label");

    char *member_count_string;
    char *member_word_string = member_count > 1 ? "Members" : "Member";
    asprintf(&member_count_string, "%d %s", member_count, member_word_string);
    gtk_label_set_text(member_count_label, member_count_string);
    mx_strdel(&member_count_string);
}

void show_chat_actions_box(void) {
    Chat *selected_chat = get_selected_chat();
    show_selected_chat_member_count(1);
    show_selected_chat_name(selected_chat->name);
    show_selected_chat_avatar(selected_chat->name[0],
                              selected_chat->image_path);
    show_chat_members();
}
