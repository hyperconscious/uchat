#include "../inc/database.h"

int mx_sub_chat(t_db_info *info, int id)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(info -> subchat_stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info -> subchat_stmt, 1, id), result);
    if(sqlite3_step(info->subchat_stmt) != SQLITE_DONE) return sqlite3_errcode(info->database);
    return 0;
}
