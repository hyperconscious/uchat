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

GtkWindow *get_window(char *id);

GtkLabel *get_label(char *id);

GtkEntry *get_entry(char *id);

char *get_entry_text(char *id);

void hide_widget(char *id);

void set_entry_icon_secondary(char *id,
                              char *icon_file_path);

void toggle_entry_visibility(char *id);

void open_window(char *id);

void close_window(char *id);
