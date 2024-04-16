#include "../inc/database.h"

int mx_check_password(t_db_info *info, int id, char *password)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(info -> checkpass_stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info -> checkpass_stmt, 1, id), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(info -> checkpass_stmt, 2, crypt(password, "pass"), -1, 0), result);
    MX_TRY_FUNCTION(sqlite3_step(info->checkpass_stmt), result);
    return sqlite3_column_count(info->checkpass_stmt);
} 
