#include "init.h"
#include "threads.h"

void loop_gui_and_client_server_communication(void) {
    pthread_t thread = create_thread(client_server_communication_thread, NULL);
    gtk_main();
    cancel_thread(thread);
    g_object_unref(Builder);
}
