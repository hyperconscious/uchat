#include "../inc/database.h"

int mx_add_user_to_chat(sqlite3_stmt *stmt, int chat_id, int user_id)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 1, user_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, chat_id), result);
    if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);
    
    return 0;
}
