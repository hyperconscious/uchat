#include "auth.h"

void on_log_in_button_clicked(void) {
    char *username = get_entry_text(LOG_IN_USERNAME_ENTRY_ID);
    char *password = get_entry_text(LOG_IN_PASSWORD_ENTRY_ID);

    if (!validate_log_in_input(username, password))
       return;

    char *result = rq_process_user_authentication(serverAddress, Port, username,
                                password, AUTH_LOGIN);
    if (strcmp(result, SUCCESSFUL) == 0){
        free(result);
        open_window(HOME_WINDOW_ID);
        close_window(AUTH_WINDOW_ID);
        return;
    }
    show_auth_error(result);
    free(result);
}

void on_sign_up_button_clicked(void) {
    char *username = get_entry_text(SIGN_UP_USERNAME_ENTRY_ID);
    char *password = get_entry_text(SIGN_UP_PASSWORD_ENTRY_ID);
    char *confirm_password = get_entry_text(SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID);

    if (!validate_sign_up_input(username, password, confirm_password))
        return;

    char *result = rq_process_user_authentication(serverAddress, Port, username,
                                password, AUTH_SIGN_UP);
    if (strcmp(result, SUCCESSFUL) == 0){
        free(result);
        open_window(HOME_WINDOW_ID);
        close_window(AUTH_WINDOW_ID);
        return;
    }
    show_auth_error(result);
    free(result);
}

void on_auth_input_change(void) {
    hide_widget(AUTH_ERROR_LABEL_ID);
}

void on_log_in_password_visibility_icon_release(void) {
    toggle_entry_visibility(LOG_IN_PASSWORD_ENTRY_ID);
}

void on_sign_up_password_visibility_icon_release(void) {
    toggle_entry_visibility(SIGN_UP_PASSWORD_ENTRY_ID);
    toggle_entry_visibility(SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID);
}

void on_sign_up_confirm_password_visibility_icon_release(void) {
    toggle_entry_visibility(SIGN_UP_PASSWORD_ENTRY_ID);
    toggle_entry_visibility(SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID);
}
