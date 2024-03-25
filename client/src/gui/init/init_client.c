#include "init.h"

void init_client(int argc, char **argv) {
    gtk_init(&argc, &argv);
    apply_css_theme();
    set_up_gtk_builder();
    open_window(AUTH_WINDOW_ID);
    loop_gui_and_client_server_communication();
}
