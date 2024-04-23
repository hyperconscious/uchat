#include "database.h"

int mx_set_read_to_all_unread_messages(sqlite3* db, int user_id, int chat_id)
{
    sqlite3_stmt *read_stmt;
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "UPDATE message SET is_readed = 1 WHERE chat_id = ? AND is_readed = 0 AND user_id != ?", -1, &read_stmt, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(read_stmt, 1, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(read_stmt, 2, user_id), result);
    if(sqlite3_step(read_stmt) != SQLITE_DONE)
    {
        return sqlite3_step(read_stmt);
    }
    return 0;
}
