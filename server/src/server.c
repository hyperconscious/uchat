#include "server.h"
#include "database.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
      fprintf(stderr, "Usage: %s <port>\n", argv[0]);
      return 1;
	  }
    // db processing...
   // mx_test_db_all();
   sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_recreate_tables(db);
    sqlite3_close(db);
    int server_socket = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(server_socket, atoi(argv[1]));
    Listen(server_socket, MAX_CLIENTS);
    while(1) {
        int client_socket = Accept(server_socket);
        
        t_client_info *client_info = malloc(sizeof(t_client_info));
        client_info->client_socket = client_socket;

      /*  pthread_t thread = */create_thread(handle_client, (void *)client_info);
     //   detach_thread(thread);
    }
    
    close(server_socket);
    return 0;
}

