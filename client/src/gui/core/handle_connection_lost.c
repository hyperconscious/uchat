#include "core.h"

void* handle_connection_lost(void* arg) {
    (void)arg;
    return NULL;
  /*  while (1) {
         if (connect_to_server()) {
             return NULL;
         }
         sleep(RETRY_INTERVAL);
    }
    return NULL;*/
}

