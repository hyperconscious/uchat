#include "../inc/database.h"

long mx_find_id_by_user(sqlite3_stmt *stmt, char* username)
{
    int result = 0;
    MX_TRY_FUNCTION(sqlite3_reset(stmt), result);
    MX_TRY_FUNCTION(sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC), result);


    long id = -1;
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        id = sqlite3_column_int64(stmt, 0); // Get the value of the 'id' column  
    }
    return id;
    
}

