#include "home.h"

Chat *create_chat(long id,
                  char *image_path,
                  char *name,
                  t_list *messages,
                  int unread_messages_count,
                  long long creation_time_in_millis) {
    Chat *chat = g_object_new(CHAT_TYPE, NULL);
    if (chat != NULL) {
        chat->id = id;
        chat->image_path = image_path != NULL ? strdup(image_path) : NULL;
        chat->name = strdup(name);
        chat->messages = messages;
        chat->unread_messages_count = unread_messages_count;
        chat->selected = false;
        chat->creation_time_in_millis = creation_time_in_millis;
    }
    return chat;
}
