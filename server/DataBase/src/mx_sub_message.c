#include "../inc/database.h"

int mx_sub_message(t_db_info *info, int id)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(info -> submsg_stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info -> submsg_stmt, 1, id), result);
    if(sqlite3_step(info->submsg_stmt) != SQLITE_DONE) return sqlite3_errcode(info->database);
    return sqlite3_reset(info -> submsg_stmt);
}

