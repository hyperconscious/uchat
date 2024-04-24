#include "database.h"

int mx_set_read_to_all_unread_messages(sqlite3* db, int user_id, int chat_id)
{
    sqlite3_stmt *read_stmt;
    sqlite3_stmt *get_last_message;

    int result = 0;

    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "SELECT last_readed_message_id FROM chat_participant WHERE user_id = ? AND chat_id = ?;", -1, &get_last_message, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(get_last_message, 2, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(get_last_message, 1, user_id), result);
    if(sqlite3_step(get_last_message) != SQLITE_ROW)
    {
        return sqlite3_step(get_last_message);
    }
    int msg_id = sqlite3_column_int64(get_last_message, 0);
    if(sqlite3_step(get_last_message) != SQLITE_DONE)
    {
        return sqlite3_step(get_last_message);
    }
    t_db_message *message = mx_get_message_by_id(db, msg_id);
    if(message == NULL)
    {
        int tmp;
        mx_get_last_messages(db, chat_id, "", 1, &message, &tmp);
        if(tmp < 1)
        {
            sqlite3_finalize(get_last_message);
            return SQLITE_ERROR;
        }
    }


    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "UPDATE chat_participant SET last_readed_message_id = ? WHERE chat_id = ? AND is_readed = 0 AND user_id != ?", -1, &read_stmt, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(read_stmt, 1, (message == NULL ? -1 : message->id)), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(read_stmt, 2, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(read_stmt, 3, user_id), result);

    if(sqlite3_step(read_stmt) != SQLITE_DONE)
    {
        return sqlite3_step(read_stmt);
    }

    sqlite3_finalize(get_last_message);
    sqlite3_finalize(read_stmt);
    return 0;
}
