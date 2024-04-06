#include "gui_util.h"

GtkWidget *get_container_first_child(GtkContainer *container) {
    GtkWidget *first_child = NULL;
    GList *children = gtk_container_get_children(GTK_CONTAINER(container));
    if (children != NULL && children->data != NULL) {
        first_child = GTK_WIDGET(children->data);
    }
    g_list_free(children);
    return first_child;
}

GtkLabel *get_label_from_container(GtkContainer *container,
                                   int label_index) {
    GList *children = gtk_container_get_children(container);
    int count_labels = 0;

    for (GList *iter = children; iter != NULL; iter = g_list_next(iter)) {
        GtkWidget *child = GTK_WIDGET(iter->data);
        if (GTK_IS_LABEL(child)) {
            if (count_labels == label_index) {
                g_list_free(children);
                return GTK_LABEL(child);
            }
            count_labels++;
        }
    }
    g_list_free(children);

    return NULL;
}

GtkBox *get_box_from_container(GtkContainer *container,
                               int box_index) {
    GList *children = gtk_container_get_children(container);
    int count_boxes = 0;

    for (GList *iter = children; iter != NULL; iter = g_list_next(iter)) {
        GtkWidget *child = GTK_WIDGET(iter->data);
        if (GTK_IS_BOX(child)) {
            if (count_boxes == box_index) {
                g_list_free(children);
                return GTK_BOX(child);
            }
            count_boxes++;
        }
    }
    g_list_free(children);

    return NULL;
}
