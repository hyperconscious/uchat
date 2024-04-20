#include "../inc/database.h"

int mx_check_password(sqlite3_stmt *stmt, int id, char *password)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, id), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 2, crypt(password, "pass"), -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_step(stmt), result);
    return sqlite3_column_count(stmt);
} 
