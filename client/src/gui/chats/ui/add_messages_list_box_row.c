#include "home.h"
#include "string_utils.h"
#include "local_time.h"

static void button_clicked_edit(GtkWidget* button, gpointer user_data){
        Message *message = (Message*)user_data;

       if(!button) printf("button edit "); 
       
       set_entry_text(CHAT_MESSAGE_ENTRY_ID, message->text);



}

static void button_clicked_delete(GtkWidget* button, gpointer user_data){
      uint32_t* id = (uint32_t*)user_data;

       if(!button) printf("button edit");


       rq_delete_message(*id, serverAddress, Port);




}

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

static void set_read_status_image(GtkBox *box,
                                  bool is_read) {
    char *read_status_image_path = is_read ? IC_HIDE_PATH : IC_SHOW_PATH;
    GtkWidget *read_status_image = GTK_WIDGET(
            image_new(read_status_image_path, 12, 12)
    );
    gtk_widget_set_margin_top(read_status_image, 2);
    gtk_widget_set_halign(read_status_image, GTK_ALIGN_START);
    add_widget_to_box(box, read_status_image, false, false, 0);
}

static void set_message_sender_name_label(GtkBox *box,
                                          char *sender_name) {
    GtkWidget *sender_name_label = gtk_label_new(sender_name);
    set_class(sender_name_label, "label_sender_name");
    add_widget_to_box(box, sender_name_label, false, false, 4);
}

static void set_message_text_label(GtkBox *box,
                                   char *text,
                                   bool is_mine,
                                   bool halign) {
    GtkWidget *text_label = gtk_label_new(text);
    GtkJustification justification = is_mine ? GTK_JUSTIFY_RIGHT
                                             : GTK_JUSTIFY_LEFT;
    gtk_label_set_line_wrap(GTK_LABEL(text_label), true);
    gtk_label_set_line_wrap_mode(GTK_LABEL(text_label), PANGO_WRAP_WORD_CHAR);
    add_widget_to_box(box, text_label, false, false, 0);
    gtk_widget_set_halign(text_label, halign);
    gtk_label_set_justify(GTK_LABEL(text_label), justification);
}

static void set_message_box(GtkBox *message_box,
                            char *text,
                            char *sender_name,
                            bool is_mine,
                            bool is_read) {
    GtkWidget *root_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *sender_name_and_read_status_box =
            gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkAlign halign = is_mine ? GTK_ALIGN_END : GTK_ALIGN_START;
    char *root_box_class = is_mine ? "message_box_mine"
                                   : "message_box_not_mine";

    set_message_text_label(GTK_BOX(root_box), text, is_mine, halign);
    set_message_sender_name_label(GTK_BOX(sender_name_and_read_status_box),
                                  sender_name);
    if (is_mine)
        set_read_status_image(GTK_BOX(sender_name_and_read_status_box),
                              is_read);

    set_class(root_box, root_box_class);

    gtk_widget_set_halign(sender_name_and_read_status_box, halign);
    gtk_widget_set_halign(root_box, halign);

    add_widget_to_box(GTK_BOX(root_box), sender_name_and_read_status_box,
                      false, false, 0);
    add_widget_to_box(message_box, root_box, false, false, 0);
}

void add_messages_list_box_row(Message *message,
                               Message *previous_message) {
    GtkWidget *message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

   
    set_messages_date_label(GTK_BOX(message_box), message->time_in_millis,
                            previous_message);
    set_message_time_label(
            GTK_BOX(message_box),
            message->time_in_millis,
            previous_message,
            message->mine
    );
    set_message_box(GTK_BOX(message_box),
                    message->text,
                    "Josh",
                    message->mine,
                    true);



    //GtkWidget *edit_button = gtk_button_new();


   
    
    if (message->mine) {
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);

    GtkWidget *edit_button = gtk_button_new();
    GtkWidget *image_edit = gtk_image_new_from_file("button_edit_image.png");
    gtk_button_set_image(GTK_BUTTON(edit_button), image_edit);

    GtkWidget *delete_button = gtk_button_new();
    GtkWidget *image_delete = gtk_image_new_from_file("button_delete_image.png");
    gtk_button_set_image(GTK_BUTTON(delete_button), image_delete);

    set_class(edit_button, "button_message");
    set_class(delete_button, "button_message");


    gtk_widget_set_halign(button_box, GTK_ALIGN_END);

    g_signal_connect(edit_button, "clicked", G_CALLBACK(button_clicked_edit), message);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(button_clicked_delete), &message->id);

    add_widget_to_box(GTK_BOX(button_box), edit_button, false, false, 0);
    add_widget_to_box(GTK_BOX(button_box), delete_button, false, false, 0);

    add_widget_to_box(GTK_BOX(message_box), button_box, false, false, 0);



}




    







    gtk_widget_show(message_box);
    gtk_widget_set_hexpand(message_box, true);

    list_box_append(CHAT_MESSAGES_LIST_ID, message_box);
}
