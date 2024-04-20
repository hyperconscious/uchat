#include "gui_util.h"

GtkImage *get_image(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_IMAGE(g_object);
}

GtkImage *image_new(char *path) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);

    g_object_unref(pixbuf);
    return GTK_IMAGE(image);
}
