#include "auth.h"

void on_log_in_button_clicked(void) {
   // char *username = get_entry_text(LOG_IN_USERNAME_ENTRY_ID);
   // char *password = get_entry_text(LOG_IN_PASSWORD_ENTRY_ID);

	//connect socket; will be replaced in function
	int client_socket = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(Port);

    Inet_pton(AF_INET, ServerAddress,
              &server_address.sin_addr); // need to be optimize
    Connect(client_socket, (struct sockaddr *)&server_address,
            sizeof(server_address));

	t_client_codes send_code = AUTH_LOGIN;
	send(client_socket, &send_code, sizeof(send_code), 0);	

	close(client_socket);

}

void on_sign_up_button_clicked(void) {
    char *username = get_entry_text(SIGN_UP_USERNAME_ENTRY_ID);
    char *password = get_entry_text(SIGN_UP_PASSWORD_ENTRY_ID);
    char *confirm_password = get_entry_text(SIGN_UP_CONFIRM_PASSWORD_ENTRY_ID);

	validate_sign_up_input(username, password, confirm_password);
	
	//connect socket; will be replaced in function
	int client_socket = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(Port);

    Inet_pton(AF_INET, ServerAddress,
              &server_address.sin_addr); // need to be optimize
    Connect(client_socket, (struct sockaddr *)&server_address,
            sizeof(server_address));

	t_client_codes send_code = AUTH_SIGN_UP;
	send(client_socket, &send_code, sizeof(send_code), 0);	
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
