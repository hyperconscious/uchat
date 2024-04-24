#include "database.h"

int mx_check_password(sqlite3_stmt *stmt, char *login, char *password)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 1, login, -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 2, crypt(password, "name"), -1, 0), result);
    return sqlite3_step(stmt) == SQLITE_ROW;
} 
