#include "home.h"
#include "string_utils.h"
#include "local_time.h"

void set_message_time_label(GtkBox *message_box,
                            long long time_in_millis,
                            Message *previous_message,
                            bool mine) {
    if (previous_message == NULL ||
        !check_time_same(time_in_millis, previous_message->time_in_millis)) {
        char *time = convert_millis_to_hour_and_minute(time_in_millis);
        GtkWidget *label = gtk_label_new(time);
        set_class(label, "message_time_label");
        GtkAlign label_halign = mine ? GTK_ALIGN_END : GTK_ALIGN_START;
        gtk_widget_set_halign(label, label_halign);
        add_widget_to_box(message_box, label, false, false, 0);
        mx_strdel(&time);
    }
}

void set_message_text_label(GtkBox *message_box,
                            char *text,
                            bool mine) {
    GtkWidget *label = gtk_label_new(text);
    GtkAlign halign = mine ? GTK_ALIGN_END : GTK_ALIGN_START;
    char *class = mine ? "message_text_label_mine"
                       : "message_text_label_not_mine";
    set_class(label, class);
    gtk_widget_set_halign(label, halign);
    add_widget_to_box(message_box, label, false, false, 0);
}

static void set_messages_date_label(GtkBox *message_box,
                                    long long time_in_millis,
                                    Message *previous_message) {
    if (previous_message == NULL ||
        !check_day_same(time_in_millis, previous_message->time_in_millis)) {
        bool include_year =
                previous_message == NULL ||
                (previous_message != NULL &&
                 !check_year_same(time_in_millis,
                                  previous_message->time_in_millis));
        char *date = convert_millis_to_date(time_in_millis, include_year);
        GtkWidget *label = gtk_label_new(date);
        gtk_widget_set_halign(label, GTK_ALIGN_START);
        add_widget_to_box(message_box, label, true, true, 0);
        set_class(label, "message_date_label");
        mx_strdel(&date);
    }
}

void add_messages_list_box_row(Message *message,
                               Message *previous_message) {
    GtkWidget *message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    gtk_widget_show(message_box);
    gtk_widget_set_hexpand(message_box, true);

    set_messages_date_label(GTK_BOX(message_box), message->time_in_millis,
                            previous_message);
    set_message_time_label(
            GTK_BOX(message_box),
            message->time_in_millis,
            previous_message,
            message->mine
    );
    set_message_text_label(GTK_BOX(message_box), message->text, message->mine);

    list_box_append(CHAT_MESSAGES_LIST_ID, message_box);
}
