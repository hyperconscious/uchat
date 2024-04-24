#include "server.h"

void daemon_work(void) {
    pid_t pid = fork();
    if(pid < 0){
        perror("fork failed");
    }
    if (pid > 0) {
        printf("Success. pid - %d\n", pid);
        exit(EXIT_SUCCESS);
    }
    pid_t sid = 0;

    sid = setsid();
    if (sid < 0) {
        perror("sid failed");
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
