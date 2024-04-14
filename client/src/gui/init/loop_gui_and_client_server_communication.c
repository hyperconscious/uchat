#include "init.h"

void loop_gui_and_client_server_communication(void) {
    gtk_main();
    g_object_unref(Builder);
}
