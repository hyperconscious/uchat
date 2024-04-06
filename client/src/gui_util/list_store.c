#include "gui_util.h"

void *get_list_store_item_by_index(GListStore *list_store,
                                   int index) {
    return g_list_model_get_item(G_LIST_MODEL(list_store), index);
}

void list_store_for_each(GListStore *list_store,
                         void (*ptr)(GObject *object)) {
    int size = g_list_model_get_n_items(G_LIST_MODEL(list_store));

    for (int i = 0; i < size; i++) {
        void *item = get_list_store_item_by_index(list_store, i);
        ptr(item);
    }
}
