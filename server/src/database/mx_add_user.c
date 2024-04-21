#include "database.h"

int mx_add_user(sqlite3_stmt *stmt, const char *name, const char *password, uint16_t lang)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 2, crypt(password, name), -1, SQLITE_STATIC), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 3, lang), result);
    int res = sqlite3_step(stmt);
    if(res != SQLITE_DONE) return res;
    return 0;
}
