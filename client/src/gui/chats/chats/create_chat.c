#include "home.h"

Chat *create_chat(long id,
                  char *image_path,
                  const char *name,
                  t_list *messages,
                  int unread_messages_count,
                  bool searching,
                  bool is_private,
                  long long creation_time_in_millis) {
    Chat *chat = g_object_new(CHAT_TYPE, NULL);
    if (chat != NULL) {
        chat->id = id;
        chat->image_path = image_path != NULL ? strdup(image_path) : NULL;
        chat->name = name != NULL ? strdup(name) : NULL;
        chat->messages = messages;
        chat->unread_messages_count = unread_messages_count;
        chat->searching = searching;
        chat->is_private = is_private;
        chat->selected = false;
        chat->creation_time_in_millis = creation_time_in_millis;
    }
    return chat;
}
