#include "gui_util.h"

GtkImage *get_image(char *id) {
    GObject *g_object = gtk_builder_get_object(Builder, id);
    return GTK_IMAGE(g_object);
}

GtkImage *image_new(char *path,
                    int width,
                    int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);

    if (width != -1 && height != -1) {
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf,
                                                           width,
                                                           height,
                                                           GDK_INTERP_BILINEAR);
        GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);
        g_object_unref(scaled_pixbuf);
        return GTK_IMAGE(image);
    }
    else {
        GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
        g_object_unref(pixbuf);
        return GTK_IMAGE(image);
    }
}
