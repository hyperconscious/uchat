#pragma once

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef void*(*FunctionPointer)(void *);

pthread_t create_thread(FunctionPointer handler, void *arg);
void join_thread(pthread_t thread, void **retval);
void cancel_thread(pthread_t thread);

