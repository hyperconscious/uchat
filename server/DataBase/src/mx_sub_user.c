#include "../inc/database.h"

int mx_sub_user(t_db_info *info, long id)
{
    int result = 0;
    TRY_FUNCTION(sqlite3_reset(info -> subusr_stmt), result);
    TRY_FUNCTION(sqlite3_bind_int(info -> subusr_stmt, 1, id), result);
    if(sqlite3_step(info->subusr_stmt) != SQLITE_DONE) return sqlite3_errcode(info->database);
    return sqlite3_reset(info -> subusr_stmt);
}
