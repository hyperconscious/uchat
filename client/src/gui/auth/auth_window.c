#include "auth.h"

void on_log_in_button_clicked(void) {
    char *username = get_entry_text(LOG_IN_USERNAME_ENTRY_ID);
    char *password = get_entry_text(LOG_IN_PASSWORD_ENTRY_ID);

    t_client_status_code server_response = process_user_authentication(serverAddress, Port,
                                                        username, password, AUTH_LOGIN);
    printf("%d", server_response);
    printf("%d", SUCCESS_LOGIN);
    switch(server_response) {
        case NO_CONNECTION_WITH_SERVER:
            //add_label;
            break;
        case WRONG_PASSWORD:
            //add label;
            break;
        case LOGIN_DOESNT_EXIST:
            //add label;
            break;
        case SUCCESS_LOGIN:
            //uchat window open();
            mx_printstr("succ login");
            break;
        default:
            mx_printstr("default login button clicked");
            break;
    }
}

void on_sign_up_button_clicked(void) {
    char *username = get_entry_text(SIGN_UP_USERNAME_ENTRY_ID);
    char *password = get_entry_text(SIGN_UP_PASSWORD_ENTRY_ID);
    char *confirm_password = get_entry_text(SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID);

	validate_sign_up_input(username, password, confirm_password);

    t_client_status_code server_response = process_user_authentication(serverAddress, Port,
                                                        username, password, AUTH_SIGN_UP);
    switch(server_response) {
        case NO_CONNECTION_WITH_SERVER:
            //add_label;
            break;
        case LOGIN_ALREADY_EXIST:
            //add label;
            break;
        case SUCCESS_REGISTRATION:
            //uchat window open();
            mx_printstr("success reg");
            break;
        default:
            break;
    }
    
}

void on_auth_input_change(void) {
    hide_widget(AUTH_ERROR_LABEL_ID);
}

void on_log_in_password_visibility_icon_release(void) {
    toggle_entry_visibility(LOG_IN_PASSWORD_ENTRY_ID);
}

void on_sign_up_password_visibility_icon_release(void) {
    toggle_entry_visibility(SIGN_UP_PASSWORD_ENTRY_ID);
}

void on_sign_up_confirm_password_visibility_icon_release(void) {
    toggle_entry_visibility(SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID);
}
