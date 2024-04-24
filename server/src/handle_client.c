#include "handle_client.h"
#include "serializer.h"

void *handle_client(void *arg) {
    t_client_info *client_info = (t_client_info *)arg;
    int client_socket = client_info->client_socket;
    free(client_info);
    
    t_packet request;
    if (!receive_packet(client_socket, &request) || request.type != PACKET_TYPE_UINT8) {
        fprintf(stderr, "Failed to receive packet from client rq\n");
        close(client_socket);
        pthread_exit(NULL);
    }
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        printf("bb");
        pthread_exit(NULL);
    }

    switch(request.u_payload.uint8_data) {
        case AUTH_LOGIN:
            handle_login(client_socket, db);
            break;
        case AUTH_SIGN_UP:
            handle_sign_up(client_socket, db);
            break;
        case RQ_SEARCH_CHAT:
            handle_search_chat(client_socket, db);
            break;
        case RQ_ADD_CHAT:
            handle_add_chat(client_socket, db);
            break;
        case RQ_GET_CHATS:
            handle_get_chats(client_socket, db);
            break;
        case RQ_ADD_USER_TO_CHAT:
            handle_add_user_to_chat(client_socket, db);
            break;
        case RQ_DISCOVER:
            handle_discover(client_socket, db);
            break;
        case RQ_GET_LOGIN_BY_ID:
            handle_get_login_by_id(client_socket, db);
            break;
        case RQ_CHANGE_USERNAME:
            handle_change_username(client_socket, db);
            break;
        case RQ_ADD_MESSAGE:
            handle_add_message(client_socket, db);
            break;
        case RQ_GET_MESSAGES:
            handle_get_messages(client_socket, db);
            break;
        default:
            fprintf(stderr, "wrong action from client\n");
            break;
    }
    sqlite3_close(db);
    close(client_socket);
    
    pthread_exit(NULL);
}

