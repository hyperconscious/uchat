#include "../inc/database.h"

int mx_check_password(t_db_info *info, long id, char *password)
{
    int result = 0;
    TRY_FUNCTION(sqlite3_reset(info -> checkpass_stmt), result);
    TRY_FUNCTION(sqlite3_bind_int(info -> checkpass_stmt, 1, id), result);
    TRY_FUNCTION(sqlite3_bind_text(info -> checkpass_stmt, 2, crypt(password, "pass"), -1, 0), result);
    TRY_FUNCTION(sqlite3_step(info->checkpass_stmt), result);
    return sqlite3_column_count(info->checkpass_stmt);
}
