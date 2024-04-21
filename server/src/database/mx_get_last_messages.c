#include "database.h"

int mx_get_last_messages(sqlite3_stmt *stmt, int chat_id, int max_rows)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, max_rows), result);
    int stat = sqlite3_step(stmt);
    if(stat != SQLITE_DONE) return stat;
    return 0;
}

