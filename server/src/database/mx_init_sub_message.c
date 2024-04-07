#include "../inc/database.h"

int mx_init_sub_message(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "DELETE FROM message WHERE id = ?", -1, statement, 0);
}
