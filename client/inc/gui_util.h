#pragma once

#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IC_SHOW_PATH "client/src/gui/layout/img/ic_show.png"
#define IC_HIDE_PATH "client/src/gui/layout/img/ic_hide.png"

extern GtkBuilder *Builder;

GtkWidget *get_widget(char *id);

bool get_widget_visible(char *id);

GtkWindow *get_window(char *id);

GtkLabel *get_label(char *id);

GtkEntry *get_entry(char *id);

void set_entry_text(char *id,
                    char *text);

GtkListBox *get_list_box(char *id);

int get_list_box_selected_item_index(char *id);

void clear_list_box(char *id);

char *get_entry_text(char *id);

void show_widget(char *id);

void hide_widget(char *id);

void set_entry_icon_secondary(char *id,
                              char *icon_file_path);

void toggle_entry_visibility(char *id);

void open_window(char *id);

void close_window(char *id);

void set_class(GtkWidget *widget,
               char *class);

void remove_class(GtkWidget *widget,
                  char *class);

int get_list_box_item_count(GtkListBox *list_box);

void list_box_for_each(GtkListBox *list_box,
                       void (*ptr)(GtkListBoxRow *row));

int get_list_box_item_count(GtkListBox *list_box);

GtkListBoxRow *list_box_append(char *id,
                               GtkWidget *widget);

void add_widget_to_box(GtkBox *box,
                       GtkWidget *widget,
                       bool expand,
                       bool fill,
                       int padding);

GtkImage *image_new(char *path);

GtkImage *get_image(char *id);

gboolean draw_circle_image(GtkWidget *widget,
                           cairo_t *cr,
                           gpointer *user_data);

gboolean draw_rounded_square_image(GtkWidget *widget,
                                   cairo_t *cr,
                                   gpointer *user_data);

GtkDrawingArea *create_drawing_area(
        int width,
        int height,
        gboolean (*callback_function)(GtkWidget *, cairo_t *, gpointer *),
        gpointer *user_data);

GtkBox *get_box(char *id);

GtkLabel *get_label_from_container(GtkContainer *container,
                                   int label_index);

GtkBox *get_box_from_container(GtkContainer *container,
                               int box_index);

GtkWidget *get_container_first_child(GtkContainer *container);

void *get_list_store_item_by_index(GListStore *list_store,
                                   int index);

void list_store_for_each(GListStore *list_store,
                         void (*ptr)(GObject *object));

gboolean scroll_window_to_bottom(gpointer user_data);

void remove_first_child_from_box(GtkBox *box);

guint get_box_child_count(GtkBox *box);

GtkFileChooser *get_file_chooser_button(char *id);

char *get_file_chooser_button_set_file_name(char *id);

GdkPixbuf *gdk_pixbuf_new_from_url(const gchar *url);
