#include "server.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
      fprintf(stderr, "Usage: %s <port>\n", argv[0]);
      return 1;
	}

<<<<<<< HEAD
    sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    //mx_recreate_tables(db);
    sqlite3_close(db);
    // db processing...
    mx_test_db_all();
=======
  /*  sqlite3 *db;
    sqlite3_open(DATABASE, &db);
    mx_recreate_tables(db);
    sqlite3_stmt *stmt;
    mx_init_add_user(db, &stmt);
    mx_add_user(stmt, "kir", "qweewq1", 0);
    mx_add_user(stmt, "val", "qweewq1", 0);
    mx_add_user(stmt, "nastya", "qweewq1", 0);
    mx_add_user(stmt, "dan", "qweewq1", 0);
    mx_add_user(stmt, "kirka", "qweewq1", 0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);*/

    // db processing...
   // mx_test_db_all();
    
>>>>>>> 9df7f4fb72868df5f7e3e121698f419d18110fe8
    int server_socket = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(server_socket, atoi(argv[1]));
    Listen(server_socket, MAX_CLIENTS);
    while(1) {
        int client_socket = Accept(server_socket);
        
        t_client_info *client_info = malloc(sizeof(t_client_info));
        client_info->client_socket = client_socket;
        
        pthread_t thread = create_thread(handle_client, (void *)client_info);
        join_thread(thread, NULL);
    }
    
    close(server_socket);
    return 0;
}

