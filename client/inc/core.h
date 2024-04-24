#pragma once

#include "gui_util.h"
#include "packet.h"
#include "socket_operations.h"
#include "client_request_codes.h"
#include "client_status_code.h"
#include "threads.h"

#define RETRY_INTERVAL 1000
#define INTERNET_CONNECTION_INDICATOR_ID "internet_connection_indicator"
#define INTERNET_CONNECTION_NOT_AVAILABLE_INDICATOR "internet_connection_not_available_indicator"
#define INTERNET_CONNECTION_AVAILABLE_INDICATOR "internet_connection_available_indicator"
#define INTERNET_CONNECTION_WAITING_INDICATOR "internet_connection_waiting_indicator"

typedef enum {
    UNAVAIBLE,
    WAITING,
    AVAIBLE
} t_connection_code;

extern char* serverAddress;
extern int Port;
extern Person *Client;

bool is_username_valid(char *username);

bool is_password_valid(char *password);

bool is_password_match(char *password1,
                       char *password2);

GtkWidget *create_avatar_widget(
        char letter,
        int size,
        char *widget_name,
        char *path,
        bool is_image_local,
        gboolean (*callback_function)(GtkWidget *, cairo_t *, gpointer *));

gboolean timer_callback(void *data);
void show_internet_connection_status(t_connection_code available);

