#include "database.h"

long mx_get_user_id_by_login(sqlite3_stmt *stmt, char *login)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 1, login, -1, 0), result);
    int stat = sqlite3_step(stmt);
    if(stat != SQLITE_ROW) return -1;
    //callback(info->get_user_id_by_login_stmt);
    return sqlite3_column_int64(stmt, 0);
}

