#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

t_list *mx_create_node(void *data);

void mx_push_front(t_list **list,
                   void *data);

void mx_push_back(t_list **list,
                  void *data);

void mx_pop_front(t_list **head);

void mx_pop_back(t_list **head);

void *mx_get_element_by_index(t_list *head,
                              int index);

void *mx_get_last_element(t_list *head);

uint32_t mx_list_size(t_list *list);
