#include "settings.h"

void on_settings_screen_show(void) {
    char *user_name = "John";
    char *image_path = NULL;
    GtkBox *change_avatar_box = get_box(CHANGE_AVATAR_BOX_ID);
    bool is_avatar_first_set = get_box_child_count(change_avatar_box) == 1;
    if (is_avatar_first_set)
        set_chosen_avatar(user_name[0], image_path, true);
}

void on_avatar_file_chooser_button_file_set(void) {
    char *file_name = get_file_chooser_button_set_file_name(
            AVATAR_FILE_CHOOSER_BUTTON);
    set_chosen_avatar(' ', file_name, false);
}

void on_change_username_button_clicked(void) {
    char *username = get_entry_text(CHANGE_USERNAME_ENTRY_ID);
    if (!validate_change_username_input(username))
        return;
}

void on_change_password_button_clicked(void) {
    char *new_password = get_entry_text(NEW_PASSWORD_ENTRY_ID);
    char *confirm_new_password = get_entry_text(CONFIRM_NEW_PASSWORD_ENTRY_ID);
    char *entered_old_password = get_entry_text(OLD_PASSWORD_ENTRY_ID);
    char *old_password = "123456a";

    if (!validate_change_password_input(new_password, confirm_new_password,
                                        old_password, entered_old_password))
        return;
}

void on_change_username_entry_text_changed(void) {
    show_change_username_error("");
}

void on_change_password_entry_text_changed(void) {
    show_change_password_error("");
}

void on_change_password_visibility_icon_release(void) {
    toggle_entry_visibility("old_password_entry");
    toggle_entry_visibility("new_password_entry");
    toggle_entry_visibility("confirm_new_password_entry");
}
