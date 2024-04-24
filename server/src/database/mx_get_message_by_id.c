#include "database.h"

t_db_message *mx_get_message_by_id(sqlite3 *db, int message_id)
{
    sqlite3_stmt *getter_stmt;
    sqlite3_prepare_v2(db, "SELECT id, text, user_id, time, chat_id FROM message WHERE id = ?", -1, &getter_stmt, 0);
    sqlite3_bind_int(getter_stmt, 1, message_id);
    if(sqlite3_step(getter_stmt) == SQLITE_ROW)
    {
        t_db_message *new_message = malloc(sizeof(t_db_chat));
        new_message->id = sqlite3_column_int64(getter_stmt, 0);
        new_message->text = strdup((const char*)sqlite3_column_text(getter_stmt, 1));
        new_message->user_id = sqlite3_column_int64(getter_stmt, 2);
        new_message->time = strdup((const char*)sqlite3_column_text(getter_stmt, 3));
        new_message->chat_id = sqlite3_column_int64(getter_stmt, 4);
        sqlite3_finalize(getter_stmt);
        return new_message;
    }
    else
    {
        sqlite3_finalize(getter_stmt);
        return NULL;
    }
}
