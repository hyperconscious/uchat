#include "database.h"

int mx_init_get_chats_by_user_id(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "SELECT chat.id, chat.name, chat.owner_id, chat.creation_time FROM chat JOIN chat_participant ON chat.id == chat_participant.chat_id AND chat_participant.user_id == ? LIMIT ?;", -1, statement, 0);
}

