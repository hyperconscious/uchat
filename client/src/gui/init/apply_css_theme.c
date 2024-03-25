#include "init.h"

void apply_css_theme(void) {
    GtkCssProvider *css_provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(css_provider, STYLES_FILE_PATH, NULL);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}
