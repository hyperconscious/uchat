#include "../inc/database.h"

int mx_sub_user(sqlite3_stmt *stmt, long id)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, id), result);
    if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);
    return 0;
}
