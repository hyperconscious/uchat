#include "auth.h"

void on_log_in_button_clicked(void) {
   char *username = get_entry_text(LOG_IN_USERNAME_ENTRY_ID);
   char *password = get_entry_text(LOG_IN_PASSWORD_ENTRY_ID);

	int client_socket = create_and_connect_socket(serverAddress, Port);

    t_client_codes mode = AUTH_LOGIN;

    t_packet login_request = create_packet(PACKET_TYPE_UINT8, &mode);
    t_packet user = create_packet(PACKET_TYPE_STRING, username);
    t_packet pass = create_packet(PACKET_TYPE_STRING, password);

    send_and_release_packet(client_socket, &login_request);
    send_and_release_packet(client_socket, &user);
    send_and_release_packet(client_socket, &pass);

	close(client_socket);

}

void on_sign_up_button_clicked(void) {
    char *username = get_entry_text(SIGN_UP_USERNAME_ENTRY_ID);
    char *password = get_entry_text(SIGN_UP_PASSWORD_ENTRY_ID);
    char *confirm_password = get_entry_text(SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID);

	validate_sign_up_input(username, password, confirm_password);
	
	int client_socket = create_and_connect_socket(serverAddress, Port);

    t_client_codes mode = AUTH_SIGN_UP; 
    t_packet login_request = create_packet(PACKET_TYPE_UINT8, &mode);
    send_and_release_packet(client_socket, &login_request);

    close(client_socket);
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
