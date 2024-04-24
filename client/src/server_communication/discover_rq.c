#include "requests.h"

Person* rq_discover(uint32_t id, uint16_t *count, char* server_address, int port){
    int client_socket = create_and_connect_socket(server_address, port);

    if(client_socket == -1)
        return NULL;

    t_client_rq rq = RQ_DISCOVER;
    t_packet get_rq = create_packet(PACKET_TYPE_UINT8, &rq);
    t_packet user_id = create_packet(PACKET_TYPE_UINT16, &id);
    send_and_release_packet(client_socket, &get_rq);
    send_and_release_packet(client_socket, &user_id);

    t_packet cc= {0};
    if(!receive_packet(client_socket, &cc)) return NULL;
    *count = cc.u_payload.uint16_data;
    Person *people = malloc(*count * sizeof(Person));

    for (uint16_t i = 0; i < *count; i++) {
        t_packet id= {0};
        t_packet name= {0};
        if(!receive_packet(client_socket, &name) || !receive_packet(client_socket, &id)) {
            for(uint16_t j = 0; j < i; j++){
                free(people[j].name);
            }
            free(people);
            return NULL;
        }
        people[i].name = name.u_payload.s_string.data;
        people[i].id = id.u_payload.uint32_data;
    }
    
    close(client_socket);
    return people; 
}

