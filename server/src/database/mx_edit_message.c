#include "database.h"

int mx_edit_message(sqlite3 *db, int message_id, char *new_text)
{
    sqlite3_stmt *stmt;
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "UPDATE message SET text = ? WHERE id = ?", -1, &stmt, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 1, new_text, -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, message_id), result);
    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        return sqlite3_step(stmt);
    }
    return 0;
    sqlite3_finalize(stmt);
}
