#include "../inc/database.h"

int mx_init_get_last_messages(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "SELECT * FROM message WHERE chat_id == ? ORDER BY time ASC LIMIT ?", -1, statement, 0);
}
