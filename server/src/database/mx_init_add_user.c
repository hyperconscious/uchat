#include "../inc/database.h"

int mx_init_add_user(sqlite3 *db, sqlite3_stmt **statement)
{    
    return sqlite3_prepare_v2(db, "INSERT INTO user_data (name, password, language) VALUES (?, ?, ?)", -1, statement, 0);
}
