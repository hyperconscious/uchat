#include "client.h"
#include "init.h"

GtkBuilder *Builder = NULL;
int Port = -1;
char* ServerAddress = NULL;

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
		return 1;
	}

	Port = atoi(argv[2]);
	ServerAddress = argv[1];

    init_client(argc, argv);
    return 0;
}
