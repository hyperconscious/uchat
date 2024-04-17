#include "user_search_rq.h"

/*t_chat_list*/void search_chats(char* searching_chat, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return;// NULL;

    t_client_rq rq = RQ_SEARCH_CHAT;
    t_packet search_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet chat_name_to_search = create_packet(PACKET_TYPE_STRING,
                                                    searching_chat);
    send_and_release_packet(client_socket, &search_rq);
    send_and_release_packet(client_socket, &chat_name_to_search);

    //t_list* founded chats = receive_packet(client_socket).u_payload.s_list;

    return;// founded chats;
}
