#include "home.h"


static void button_clicked(GtkWidget* button, gpointer user_data){
       char* username = (char*) user_data;

       if(button) printf("button ");


        set_home_header_button_active_style(CHATS_BUTTON_ID);
        hide_widget(SETTINGS_BOX_ID);
        hide_widget(DISCOVER_BOX_ID);
        show_widget(CHATS_BOX_ID);


		set_entry_text(SEARCH_CHAT_ENTRY_ID, username);



}


GtkWidget *create_discover_grid_item(Person founded_chat) {

        
    GtkWidget *discover_grid_item = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    GtkWidget *avatar_widget = create_avatar_widget(
            founded_chat.name[0],
            120,
            "circle_default_avatar",
            founded_chat.image_url,
            true,
            draw_circle_image
    );
    GtkWidget *name_widget = gtk_label_new(founded_chat.name);
    GtkWidget *start_messaging_button =
            gtk_button_new_with_label("Start messaging");

    gtk_widget_set_halign(avatar_widget, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(name_widget, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(start_messaging_button, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(discover_grid_item, true);

    set_class(start_messaging_button, "button_primary");
    set_class(discover_grid_item, "discover_grid_item");

    gtk_label_set_ellipsize(GTK_LABEL(name_widget), PANGO_ELLIPSIZE_END);
        char* aaa = strdup(founded_chat.name);
        g_signal_connect(start_messaging_button, "clicked", G_CALLBACK(button_clicked), aaa);

    add_widget_to_box(GTK_BOX(discover_grid_item), avatar_widget, false,
                      false, 0);
    add_widget_to_box(GTK_BOX(discover_grid_item), name_widget, true,
                      false, 8);
    add_widget_to_box(GTK_BOX(discover_grid_item), start_messaging_button,
                      false, false, 0);
    gtk_widget_show(discover_grid_item);

    return discover_grid_item;
}
