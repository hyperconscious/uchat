#include "gui_util.h"

gboolean draw_circle_image(GtkWidget *widget,
                           cairo_t *cr,
                           gpointer *user_data) {
    char *image_path = (char *)user_data;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_path, NULL);

    gint widget_width = gtk_widget_get_allocated_width(widget);
    gint widget_height = gtk_widget_get_allocated_height(widget);
    double center_x = widget_width / 2.0;
    double center_y = widget_height / 2.0;
    double image_width = gdk_pixbuf_get_width(pixbuf);
    double image_height = gdk_pixbuf_get_height(pixbuf);
    double scale = MAX(widget_width / image_width,
                       widget_height / image_height);

    double image_x = center_x - image_width * scale / 2.0;
    double image_y = center_y - image_height * scale / 2.0;
    double radius = 0.5 * MIN(widget_width, widget_height);

    cairo_new_path(cr);
    cairo_arc(cr, center_x, center_y, radius, 0, 2 * G_PI);
    cairo_close_path(cr);
    cairo_clip(cr);
    cairo_save(cr);
    cairo_scale(cr, scale, scale);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, image_x / scale, image_y / scale);
    cairo_paint(cr);
    cairo_restore(cr);
    cairo_reset_clip(cr);
    g_object_unref(pixbuf);
    return FALSE;
}

gboolean draw_rounded_square_image(GtkWidget *widget,
                                   cairo_t *cr,
                                   gpointer *user_data) {
    char *image_path = (char *)user_data;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_path, NULL);

    gint widget_width = gtk_widget_get_allocated_width(widget);
    gint widget_height = gtk_widget_get_allocated_height(widget);
    double image_x = widget_width / 2 - gdk_pixbuf_get_width(pixbuf) / 2.0;
    double image_y = widget_height / 2 - gdk_pixbuf_get_height(pixbuf) / 2.0;
    double corner_radius = 20.0;

    cairo_new_path(cr);
    cairo_move_to(cr, corner_radius, 0);
    cairo_line_to(cr, widget_width - corner_radius, 0);
    cairo_arc(cr, widget_width - corner_radius, corner_radius, corner_radius,
              -G_PI / 2, 0);
    cairo_line_to(cr, widget_width, widget_height - corner_radius);
    cairo_arc(cr, widget_width - corner_radius, widget_height - corner_radius,
              corner_radius,
              0, G_PI / 2);
    cairo_line_to(cr, corner_radius, widget_height);
    cairo_arc(cr, corner_radius, widget_height - corner_radius, corner_radius,
              G_PI / 2, G_PI);
    cairo_line_to(cr, 0, corner_radius);
    cairo_arc(cr, corner_radius, corner_radius, corner_radius, G_PI,
              3 * G_PI / 2);
    cairo_close_path(cr);
    cairo_clip(cr);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, image_x, image_y);
    cairo_paint(cr);
    cairo_reset_clip(cr);
    g_object_unref(pixbuf);
    return FALSE;
}
