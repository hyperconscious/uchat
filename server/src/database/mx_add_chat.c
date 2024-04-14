#include "../inc/database.h"

int mx_add_chat(t_db_info *info, char *name, int owner_id, int *id_of_new_chat)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(info->addchat_stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(info->addchat_stmt, 1, name, -1, SQLITE_STATIC), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(info->addchat_stmt, 2, owner_id), result);
    if(sqlite3_step(info->addchat_stmt) != SQLITE_DONE) return sqlite3_errcode(info->database);
    *id_of_new_chat = sqlite3_last_insert_rowid(info->database);
    return 0;
}

