#include "core.h"
#include "home.h"


static gboolean check_chat_id(gconstpointer a,
                                       gconstpointer b) {
    Chat *chat1 = (Chat *)a;
    Chat *chat2 = (Chat *)b;
    return chat1->id == chat2->id;
}

void free_data(GObject *object) {
    Chat *chat = (Chat *)object;
    if(chat && !chat->searching){
        if(chat->image_path){
            free(chat->image_path);
        }
        if(chat->name){
            free(chat->name);
        }
        if(chat->messages){
            t_list *curr = chat->messages;
            while (curr != NULL) {
                Message * msg = curr->data;
                if(msg->text)
                    free(msg->text);
                curr = curr->next;
              //  free(msg);
            }
        }
    }
    
}

void clear_lists() {
    list_store_for_each(all_chats_list_store, free_data);
    list_store_for_each(visible_chats_list_store, free_data);
    g_list_store_remove_all(visible_chats_list_store);
    g_list_store_remove_all(visible_chats_list_store);
}

void foo(GObject *object) {
    Chat *chat = (Chat *)object;
    add_chat_sorted_to_visible_list_store(chat);
}

gboolean timer_callback() {
    if(Client->name != NULL){
        int socket = create_and_connect_socket(serverAddress, Port);
        if(socket != -1){
            t_client_rq rq = CONNECTION;
            t_packet request = create_packet(PACKET_TYPE_UINT8, &rq);
            t_packet heart = create_packet(PACKET_TYPE_UINT8,
                                          &(t_client_status_code){SUCCESS});
            send_and_release_packet(socket, &request);
            send_and_release_packet(socket, &heart);
            t_packet response;
            if(!receive_packet(socket, &response)) {
                show_internet_connection_status(WAITING);
                /* pthread_t thread = create_thread(handle_connection_lost, NULL);
                join_thread(thread, NULL);*/
            } else {
                show_internet_connection_status(AVAIBLE);
                t_list *new_chats = get_chats();
                uint32_t chats_count = mx_list_size(new_chats);
                for (uint32_t i = 0; i < chats_count; i++) {
                    guint index = 0;
                    Chat *chat = mx_get_element_by_index(new_chats, i);
                    
                    if(g_list_store_find_with_equal_func(all_chats_list_store,
                                chat, check_chat_id, &index)){
                        Chat *my = get_list_store_item_by_index(all_chats_list_store,
                                                     index);
                       /*     guint previous_selected_chat_index;
                            bool is_chat_selected =
                                    get_selected_chat_index(&previous_selected_chat_index);

                            set_chat_list_box_row_selected_style(selected_row);

                            if (!is_chat_selected || !selected_chat->selected) {
                                if (is_chat_selected)
                                    unselect_previous_selected_chat(previous_selected_chat_index);

                                remove_previous_chat_avatar_if_set();
                                selected_chat->selected = true;
                                set_chat_name(selected_chat->name);
                                set_chat_image(selected_chat->image_path, selected_chat->name[0]);
                                set_chat_messages(selected_chat->messages);
                                set_messages_read(selected_row, selected_chat);
                                show_chat_box();
                                g_timeout_add(50, scroll_window_to_bottom,
                                              CHAT_MESSAGES_SCROLLED_WINDOW_ID);
                                    }

                            if (get_widget_visible(CHAT_ACTIONS_BOX_ID)) {
                                hide_widget(CHAT_ACTIONS_BOX_ID);
                                show_widget(CHAT_BOX_ID);
                            }*/
                        my->messages = chat->messages;
                        clear_list_box(CHAT_MESSAGES_LIST_ID);
                        Message *previous_message = NULL;
                        int messages_count = mx_list_size(my->messages);
                        for (int i = 0; i < messages_count; i++) {
                            Message *message = mx_get_element_by_index(my->messages, i);
                            if (message != NULL) {
                                add_messages_list_box_row(message, previous_message);
                                previous_message = message;
                            }
                        }
                    } else {
                        add_chat_sorted_to_all_list_store(chat);
                    }
                }
                g_list_store_remove_all(visible_chats_list_store);
                list_store_for_each(all_chats_list_store, foo);
                guint select = 0;
                get_selected_chat_index(&select);
                if(select)
                    select_chat(gtk_list_box_get_row_at_index(get_list_box(CHAT_LIST_BOX_ID),
                                select));
            }
        } else {
            show_internet_connection_status(UNAVAIBLE);
            close(socket);
        }
    }
    return TRUE;
}

