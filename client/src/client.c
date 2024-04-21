#include "client.h"

GtkBuilder *Builder = NULL;
int Port = -1;
char* serverAddress = NULL;
uint32_t user_id = 13;

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"ip\" <port>\n", argv[0]);
        return 1;
    }

    Port = atoi(argv[2]);
    serverAddress = argv[1];

    init_client(argc, argv);
    return 0;
}
