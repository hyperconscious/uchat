#include "gui_util.h"

gboolean draw_circle_image(GtkWidget *widget,
                           cairo_t *cr,
                           gpointer *user_data) {
    char *image_path = (char *)user_data;
    cairo_surface_t *image = cairo_image_surface_create_from_png(image_path);
    gint widget_width = gtk_widget_get_allocated_width(widget);
    gint widget_height = gtk_widget_get_allocated_height(widget);
    double center_x = widget_width / 2.0;
    double center_y = widget_height / 2.0;
    double image_x = center_x - cairo_image_surface_get_width(image) / 2.0;
    double image_y = center_y - cairo_image_surface_get_height(image) / 2.0;
    double radius = 0.5 * MIN(widget_width, widget_height);

    cairo_new_path(cr);
    cairo_arc(cr, center_x, center_y, radius, 0, 2 * G_PI);
    cairo_close_path(cr);
    cairo_clip(cr);
    cairo_set_source_surface(cr, image, image_x, image_y);
    cairo_paint(cr);
    cairo_reset_clip(cr);
    return FALSE;
}

gboolean draw_rounded_square_image(GtkWidget *widget,
                                   cairo_t *cr,
                                   gpointer *user_data) {
    char *image_path = (char *)user_data;
    cairo_surface_t *image = cairo_image_surface_create_from_png(image_path);
    gint widget_width = gtk_widget_get_allocated_width(widget);
    gint widget_height = gtk_widget_get_allocated_height(widget);
    double image_x = widget_width / 2 - cairo_image_surface_get_width(image) / 2.0;
    double image_y = widget_height / 2 - cairo_image_surface_get_height(image) / 2.0;
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
    cairo_set_source_surface(cr, image, image_x, image_y);
    cairo_paint(cr);
    cairo_reset_clip(cr);
    cairo_surface_destroy(image);
    return FALSE;
}
