#include "database.h"

int mx_add_chat(sqlite3_stmt *stmt, char *name, int owner_id, bool is_private)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 2, owner_id), result);
    MX_TRY_FUNCTION(sqlite3_bind_int(stmt, 3, is_private), result);
    if(sqlite3_step(stmt) != SQLITE_DONE)
        return sqlite3_step(stmt);
    //int chat_id = sqlite3_get_last_inserted_row_id(db);
    return 0;
}

