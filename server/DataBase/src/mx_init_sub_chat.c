#include "../inc/database.h"

int mx_init_sub_chat(sqlite3 *db, sqlite3_stmt **statement)
{
    return sqlite3_prepare_v2(db, "DELETE FROM chats WHERE id = ?", -1, statement, 0);
}
