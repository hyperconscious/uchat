#include "database.h"

int mx_remove_message(sqlite3 *db, int message_id)
{
    int result = 0;
    sqlite3_stmt *stmt;
    MX_TRY_FUNCTION(sqlite3_prepare_v2(db, "DELETE FROM message WHERE id = ?", -1, &stmt, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, message_id), result);
    return sqlite3_finalize(stmt);
}
