#include "../inc/database.h"

int mx_add_message(t_db_info *info, char *text, int user_id, int chat_id, float time)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(info->addmsg_stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_double(info->addmsg_stmt, 1, time), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info->addmsg_stmt, 2, user_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info->addmsg_stmt, 3, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(info->addusr_stmt, 4, text, -1, SQLITE_STATIC), result);
    if(sqlite3_step(info->addmsg_stmt) != SQLITE_DONE) return sqlite3_errcode(info->database);
    
    return 0;
}
