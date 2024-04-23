#include "requests.h"

t_db_chat* rq_get_chats(uint32_t owner_id, uint16_t *count, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NULL;

    t_client_rq rq = RQ_GET_CHATS;
    t_packet get_rq = create_packet(PACKET_TYPE_UINT8, &rq);

    t_packet owner_id_packet = create_packet(PACKET_TYPE_UINT32, &owner_id);
    send_and_release_packet(client_socket, &get_rq);
    send_and_release_packet(client_socket, &owner_id_packet);

    t_packet cc;
    if(!receive_packet(client_socket, &cc)) return NULL;
    *count = cc.u_payload.uint16_data;
    t_db_chat *chats_array = malloc(*count * sizeof(t_db_chat));
    for (uint16_t i = 0; i < *count; i++) {
        t_packet id;
        t_packet owner_id;
        t_packet name;
        t_packet time;
        if(!receive_packet(client_socket, &id) 
        || !receive_packet(client_socket, &owner_id) 
        || !receive_packet(client_socket, &name)
        || !receive_packet(client_socket, &time)) {
            for(uint16_t j = 0; j < i; j++){
                free(chats_array[j].name);
                free(chats_array[j].creation_time);
            }
            free(chats_array);
            return NULL;
        }
        (chats_array + i)->id = id.u_payload.uint32_data;
        (chats_array + i)->owner_id = owner_id.u_payload.uint32_data;
        (chats_array + i)->name = strdup(name.u_payload.s_string.data);
        (chats_array + i)->creation_time = strdup(name.u_payload.s_string.data);
        free_packet(&name);
        free_packet(&time);
    }
     
    close(client_socket);
    return chats_array;
}

