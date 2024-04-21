#include "../inc/database.h"

int mx_init_find_id_by_user(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "SELECT id FROM user_data WHERE name LIKE \%?\%", -1, statement, 0);
}
