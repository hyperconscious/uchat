#include "client.h"

GtkBuilder *Builder = NULL;
int Port = -1;
Person *Client = NULL;
char* serverAddress = NULL;

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"ip\" <port>\n", argv[0]);
        return 1;
    }

    Port = atoi(argv[2]);
    serverAddress = argv[1];
    Person user = {.id = 0, .name = NULL, .image_url = NULL};
    Client = &user;
    init_client(argc, argv);
    return 0;
}
