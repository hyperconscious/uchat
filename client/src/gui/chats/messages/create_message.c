#include "home.h"

Message *create_message(const char *text,
                        bool mine,
                        long long time_in_millis) {
    Message *message = malloc(sizeof(Message));
    if (message != NULL) {
        message->text = strdup(text);
        message->mine = mine;
        message->time_in_millis = time_in_millis;
    }
    return message;
}