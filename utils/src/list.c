#include "list.h"

t_list *mx_create_node(void *data) {
    t_list *node = malloc(sizeof(t_list));

    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

void mx_push_front(t_list **list,
                   void *data) {
    t_list *node = mx_create_node(data);

    node->next = *list;
    *list = node;
}

void mx_push_back(t_list **list,
                  void *data) {
    t_list *node = mx_create_node(data);
    t_list *current = *list;

    if (*list == NULL) {
        *list = node;
        return;
    }

    while (current->next != NULL)
        current = current->next;

    current->next = node;
}

void mx_pop_front(t_list **head) {
    if (head == NULL || *head == NULL)
        return;

    t_list *current_head = *head;
    *head = (*head)->next;
    free(current_head);
}

void mx_pop_back(t_list **head) {
    if (head == NULL || *head == NULL)
        return;

    if ((*head)->next != NULL) {
        t_list *current_list = *head;
        while (current_list->next->next != NULL) {
            current_list = current_list->next;
        }
        free(current_list->next);
        current_list->next = NULL;
    }
    else {
        free(*head);
        (*head) = NULL;
    }
}

void *mx_get_element_by_index(t_list *head,
                              int index) {
    t_list *current = head;
    int i = 0;

    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    return current != NULL ? current->data : NULL;
}

int mx_list_size(t_list *list) {
    int size = 0;

    while (list != NULL) {
        size++;
        list = list->next;
    }

    return size;
}

void *mx_get_last_element(t_list *head) {
    t_list *current = head;

    while (current != NULL && current->next != NULL)
        current = current->next;

    return current != NULL ? current->data : NULL;
}
