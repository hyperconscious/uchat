#include "init.h"

GtkBuilder *Builder = NULL;

int main(int argc, char **argv) {
    init_client(argc, argv);
    return 0;
}
