#include "../inc/database.h"

int mx_get_last_messages(t_db_info *info, int chat_id, int max_rows, void(*callback)(sqlite3_stmt*))
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(info->get_last_messages_stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info->get_last_messages_stmt, 1, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info->get_last_messages_stmt, 2, max_rows), result);
    if(sqlite3_step(info->get_last_messages_stmt) != SQLITE_DONE) return sqlite3_errcode(info->database);
    callback(info->get_last_messages_stmt);
}

