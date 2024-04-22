#include "settings.h"

void set_chosen_avatar(char user_name_first_letter,
                       char *image_path,
                       bool is_first_set) {
    GtkBox *change_avatar_box = get_box(CHANGE_AVATAR_BOX_ID);
    if (!is_first_set)
        remove_child_from_box(change_avatar_box, 0);
    GtkWidget *avatar_widget = create_avatar_widget(
            user_name_first_letter,
            120,
            "circle_default_avatar",
            image_path,
            true,
            draw_circle_image
    );
    add_widget_to_box(change_avatar_box, avatar_widget, false, false, 0);
    gtk_box_reorder_child(change_avatar_box, avatar_widget, 0);
}
