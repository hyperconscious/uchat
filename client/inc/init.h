#pragma once

#include "gui_util.h"

#define STYLES_FILE_PATH "client/src/gui/layout/style.css"
#define GLADE_FILE_PATH "client/src/gui/layout/layout.glade"
#define AUTH_WINDOW_ID "auth_window"

void set_up_gtk_builder(void);

void apply_css_theme(void);

void init_client(int argc,
                 char **argv);

void *client_server_communication_thread(void *arg);

void loop_gui_and_client_server_communication(void);
