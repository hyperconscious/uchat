#include "threads.h"

pthread_t create_thread(FunctionPointer func, void *arg) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, func, (void *)arg) != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }
    return thread_id;
}

void join_thread(pthread_t thread, void **retval) {
    if (pthread_join(thread, retval) != 0) {
        perror("join_thread failed");
        exit(EXIT_FAILURE);
    }
}

