#include "../inc/database.h"

int mx_add_user(t_db_info *info, const char *name, const char *password, int *id_of_new_user)
{
    int result = 0;
    TRY_FUNCTION(sqlite3_reset(info->addusr_stmt), result);
    TRY_FUNCTION(sqlite3_bind_text(info->addusr_stmt, 1, name, -1, SQLITE_STATIC), result);
    TRY_FUNCTION(sqlite3_bind_text(info->addusr_stmt, 2, crypt(password, "pass"), -1, SQLITE_STATIC), result);
    if( sqlite3_step(info->addusr_stmt) != SQLITE_DONE) return sqlite3_step(info->addusr_stmt);

    *id_of_new_user = sqlite3_last_insert_rowid(info->database);

    return 0;
}
