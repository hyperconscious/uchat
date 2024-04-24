#include "core.h"
#include "home.h"


static gboolean check_chat_id(gconstpointer a,
                                       gconstpointer b) {
    Chat *chat1 = (Chat *)a;
    Chat *chat2 = (Chat *)b;
    return chat1->id == chat2->id;
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
                        my->messages = chat->messages;
                        clear_list_box(CHAT_MESSAGES_LIST_ID);
                        Message *previous_message = NULL;
                        if (my->messages == NULL)
                            continue;
                        int messages_count = mx_list_size(my->messages);
                        for (int i = 0; i < messages_count; i++) {
                            Message *message = mx_get_element_by_index(my->messages, i);
                            if (message != NULL) {
                                add_messages_list_box_row(message, previous_message);
                                previous_message = message;
                            }
                        }
                    } else if (strlen(get_entry_text(SEARCH_CHAT_ENTRY_ID)) == 0) {
                        add_chat_sorted(chat);
                    } else
                        add_chat_sorted_to_all_list_store(chat);
                }
            }
        } else {
            show_internet_connection_status(UNAVAIBLE);
            close(socket);
        }
    }
    return TRUE;
}

