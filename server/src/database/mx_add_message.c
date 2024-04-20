#include "../inc/database.h"

int mx_add_message(sqlite3_stmt *stmt, char *text, int user_id, int chat_id, float time)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_double(stmt, 1, time), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, user_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 3, chat_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 4, text, -1, SQLITE_STATIC), result);
    if(sqlite3_step(stmt) != SQLITE_DONE) return sqlite3_step(stmt);
    
    return 0;
}
