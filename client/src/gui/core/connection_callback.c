#include "core.h"
#include "home.h"

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
             /*   int size = g_list_model_get_n_items(G_LIST_MODEL(all_chats_list_store));
                for (int i = 0; i < size; i++) {
                    Chat *chat = get_list_store_item_by_index(all_chats_list_store, i);
                    t_list *msgs = rq_get_messages_from_chat(chat->id, "",
                                                     serverAddress, Port);
                    t_list *curr = msgs;
                    t_list *res = NULL;
                    while(curr != NULL){
                        Message *msg = create_message(((t_db_message*)curr->data)->text,
                                                     ((t_db_message *)curr->data)->user_id ==
                                                     Client->id,
                                                     convert_to_epoch(((t_db_message
                                                                 *)curr->data)->time));
                        free(((t_db_message*)curr->data)->text);
                        free(((t_db_message*)curr->data)->time);
                        curr = curr->next;
                        mx_push_back(&res, msg);
                    }
                    chat->messages = res;
                }*/
            }
        } else {
                show_internet_connection_status(UNAVAIBLE);
        }
        close(socket);
    }
    return TRUE;
}

