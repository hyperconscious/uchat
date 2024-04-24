#include "init.h"

void init_client(int argc, char **argv) {
    gtk_init(&argc, &argv);
    apply_css_theme();
    set_up_gtk_builder();
    guint timer_id = g_timeout_add(RETRY_INTERVAL, (GSourceFunc)timer_callback, NULL);
    open_window(AUTH_WINDOW_ID);
 //   open_window("home_window");
    gtk_main();
    g_object_unref(Builder);
    g_source_remove(timer_id);
}
