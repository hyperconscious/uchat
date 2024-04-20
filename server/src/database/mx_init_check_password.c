#include "../inc/database.h"

int mx_init_check_password(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "SELECT id FROM user_data WHERE id = ? AND password = ?", -1, statement, 0);
}
